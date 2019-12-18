#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct netns_ipvs {scalar_t__ sync_state; } ;
struct net {int dummy; } ;
struct ip_vs_service_user_kern {int dummy; } ;
struct ip_vs_service {scalar_t__ af; } ;
struct ip_vs_dest_user_kern {scalar_t__ af; int conn_flags; } ;
struct genl_info {int /*<<< orphan*/ * attrs; TYPE_1__* genlhdr; } ;
struct TYPE_2__ {int cmd; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EEXIST ; 
 int EINVAL ; 
 int ESRCH ; 
 size_t IPVS_CMD_ATTR_DEST ; 
 size_t IPVS_CMD_ATTR_SERVICE ; 
#define  IPVS_CMD_DEL_DEST 135 
#define  IPVS_CMD_DEL_SERVICE 134 
 int IPVS_CMD_FLUSH ; 
#define  IPVS_CMD_NEW_DEST 133 
#define  IPVS_CMD_NEW_SERVICE 132 
 int IPVS_CMD_SET_CONFIG ; 
#define  IPVS_CMD_SET_DEST 131 
#define  IPVS_CMD_SET_SERVICE 130 
#define  IPVS_CMD_ZERO 129 
#define  IP_VS_CONN_F_TUNNEL 128 
 int /*<<< orphan*/  __ip_vs_mutex ; 
 int ip_vs_add_dest (struct ip_vs_service*,struct ip_vs_dest_user_kern*) ; 
 int ip_vs_add_service (struct netns_ipvs*,struct ip_vs_service_user_kern*,struct ip_vs_service**) ; 
 int ip_vs_del_dest (struct ip_vs_service*,struct ip_vs_dest_user_kern*) ; 
 int ip_vs_del_service (struct ip_vs_service*) ; 
 int ip_vs_edit_dest (struct ip_vs_service*,struct ip_vs_dest_user_kern*) ; 
 int ip_vs_edit_service (struct ip_vs_service*,struct ip_vs_service_user_kern*) ; 
 int ip_vs_flush (struct netns_ipvs*,int) ; 
 int ip_vs_genl_parse_dest (struct ip_vs_dest_user_kern*,int /*<<< orphan*/ ,int) ; 
 int ip_vs_genl_parse_service (struct netns_ipvs*,struct ip_vs_service_user_kern*,int /*<<< orphan*/ ,int,struct ip_vs_service**) ; 
 int ip_vs_genl_set_config (struct netns_ipvs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_is_af_valid (scalar_t__) ; 
 int ip_vs_zero_all (struct netns_ipvs*) ; 
 int ip_vs_zero_service (struct ip_vs_service*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct netns_ipvs* net_ipvs (struct net*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_genl_set_cmd(struct sk_buff *skb, struct genl_info *info)
{
	bool need_full_svc = false, need_full_dest = false;
	struct ip_vs_service *svc = NULL;
	struct ip_vs_service_user_kern usvc;
	struct ip_vs_dest_user_kern udest;
	int ret = 0, cmd;
	struct net *net = sock_net(skb->sk);
	struct netns_ipvs *ipvs = net_ipvs(net);

	cmd = info->genlhdr->cmd;

	mutex_lock(&__ip_vs_mutex);

	if (cmd == IPVS_CMD_FLUSH) {
		ret = ip_vs_flush(ipvs, false);
		goto out;
	} else if (cmd == IPVS_CMD_SET_CONFIG) {
		ret = ip_vs_genl_set_config(ipvs, info->attrs);
		goto out;
	} else if (cmd == IPVS_CMD_ZERO &&
		   !info->attrs[IPVS_CMD_ATTR_SERVICE]) {
		ret = ip_vs_zero_all(ipvs);
		goto out;
	}

	/* All following commands require a service argument, so check if we
	 * received a valid one. We need a full service specification when
	 * adding / editing a service. Only identifying members otherwise. */
	if (cmd == IPVS_CMD_NEW_SERVICE || cmd == IPVS_CMD_SET_SERVICE)
		need_full_svc = true;

	ret = ip_vs_genl_parse_service(ipvs, &usvc,
				       info->attrs[IPVS_CMD_ATTR_SERVICE],
				       need_full_svc, &svc);
	if (ret)
		goto out;

	/* Unless we're adding a new service, the service must already exist */
	if ((cmd != IPVS_CMD_NEW_SERVICE) && (svc == NULL)) {
		ret = -ESRCH;
		goto out;
	}

	/* Destination commands require a valid destination argument. For
	 * adding / editing a destination, we need a full destination
	 * specification. */
	if (cmd == IPVS_CMD_NEW_DEST || cmd == IPVS_CMD_SET_DEST ||
	    cmd == IPVS_CMD_DEL_DEST) {
		if (cmd != IPVS_CMD_DEL_DEST)
			need_full_dest = true;

		ret = ip_vs_genl_parse_dest(&udest,
					    info->attrs[IPVS_CMD_ATTR_DEST],
					    need_full_dest);
		if (ret)
			goto out;

		/* Old protocols did not allow the user to specify address
		 * family, so we set it to zero instead.  We also didn't
		 * allow heterogeneous pools in the old code, so it's safe
		 * to assume that this will have the same address family as
		 * the service.
		 */
		if (udest.af == 0)
			udest.af = svc->af;

		if (!ip_vs_is_af_valid(udest.af)) {
			ret = -EAFNOSUPPORT;
			goto out;
		}

		if (udest.af != svc->af && cmd != IPVS_CMD_DEL_DEST) {
			/* The synchronization protocol is incompatible
			 * with mixed family services
			 */
			if (ipvs->sync_state) {
				ret = -EINVAL;
				goto out;
			}

			/* Which connection types do we support? */
			switch (udest.conn_flags) {
			case IP_VS_CONN_F_TUNNEL:
				/* We are able to forward this */
				break;
			default:
				ret = -EINVAL;
				goto out;
			}
		}
	}

	switch (cmd) {
	case IPVS_CMD_NEW_SERVICE:
		if (svc == NULL)
			ret = ip_vs_add_service(ipvs, &usvc, &svc);
		else
			ret = -EEXIST;
		break;
	case IPVS_CMD_SET_SERVICE:
		ret = ip_vs_edit_service(svc, &usvc);
		break;
	case IPVS_CMD_DEL_SERVICE:
		ret = ip_vs_del_service(svc);
		/* do not use svc, it can be freed */
		break;
	case IPVS_CMD_NEW_DEST:
		ret = ip_vs_add_dest(svc, &udest);
		break;
	case IPVS_CMD_SET_DEST:
		ret = ip_vs_edit_dest(svc, &udest);
		break;
	case IPVS_CMD_DEL_DEST:
		ret = ip_vs_del_dest(svc, &udest);
		break;
	case IPVS_CMD_ZERO:
		ret = ip_vs_zero_service(svc);
		break;
	default:
		ret = -EINVAL;
	}

out:
	mutex_unlock(&__ip_vs_mutex);

	return ret;
}