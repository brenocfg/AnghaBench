#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct mpls_iptunnel_encap {scalar_t__ default_ttl; int /*<<< orphan*/  ttl_propagate; int /*<<< orphan*/ * label; int /*<<< orphan*/  labels; } ;
struct lwtunnel_state {int /*<<< orphan*/  headroom; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LWTUNNEL_ENCAP_MPLS ; 
 int /*<<< orphan*/  LWTUNNEL_STATE_XMIT_REDIRECT ; 
 int /*<<< orphan*/  MAX_NEW_LABELS ; 
 size_t MPLS_IPTUNNEL_DST ; 
 int /*<<< orphan*/  MPLS_IPTUNNEL_MAX ; 
 size_t MPLS_IPTUNNEL_TTL ; 
 int /*<<< orphan*/  MPLS_TTL_PROP_DEFAULT ; 
 int /*<<< orphan*/  MPLS_TTL_PROP_DISABLED ; 
 int /*<<< orphan*/  MPLS_TTL_PROP_ENABLED ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  kfree (struct lwtunnel_state*) ; 
 int /*<<< orphan*/  label ; 
 struct lwtunnel_state* lwtunnel_state_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpls_encap_size (struct mpls_iptunnel_encap*) ; 
 int /*<<< orphan*/  mpls_iptunnel_policy ; 
 struct mpls_iptunnel_encap* mpls_lwtunnel_encap (struct lwtunnel_state*) ; 
 int nla_get_labels (struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  struct_size (struct mpls_iptunnel_encap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpls_build_state(struct nlattr *nla,
			    unsigned int family, const void *cfg,
			    struct lwtunnel_state **ts,
			    struct netlink_ext_ack *extack)
{
	struct mpls_iptunnel_encap *tun_encap_info;
	struct nlattr *tb[MPLS_IPTUNNEL_MAX + 1];
	struct lwtunnel_state *newts;
	u8 n_labels;
	int ret;

	ret = nla_parse_nested_deprecated(tb, MPLS_IPTUNNEL_MAX, nla,
					  mpls_iptunnel_policy, extack);
	if (ret < 0)
		return ret;

	if (!tb[MPLS_IPTUNNEL_DST]) {
		NL_SET_ERR_MSG(extack, "MPLS_IPTUNNEL_DST attribute is missing");
		return -EINVAL;
	}

	/* determine number of labels */
	if (nla_get_labels(tb[MPLS_IPTUNNEL_DST], MAX_NEW_LABELS,
			   &n_labels, NULL, extack))
		return -EINVAL;

	newts = lwtunnel_state_alloc(struct_size(tun_encap_info, label,
						 n_labels));
	if (!newts)
		return -ENOMEM;

	tun_encap_info = mpls_lwtunnel_encap(newts);
	ret = nla_get_labels(tb[MPLS_IPTUNNEL_DST], n_labels,
			     &tun_encap_info->labels, tun_encap_info->label,
			     extack);
	if (ret)
		goto errout;

	tun_encap_info->ttl_propagate = MPLS_TTL_PROP_DEFAULT;

	if (tb[MPLS_IPTUNNEL_TTL]) {
		tun_encap_info->default_ttl = nla_get_u8(tb[MPLS_IPTUNNEL_TTL]);
		/* TTL 0 implies propagate from IP header */
		tun_encap_info->ttl_propagate = tun_encap_info->default_ttl ?
			MPLS_TTL_PROP_DISABLED :
			MPLS_TTL_PROP_ENABLED;
	}

	newts->type = LWTUNNEL_ENCAP_MPLS;
	newts->flags |= LWTUNNEL_STATE_XMIT_REDIRECT;
	newts->headroom = mpls_encap_size(tun_encap_info);

	*ts = newts;

	return 0;

errout:
	kfree(newts);
	*ts = NULL;

	return ret;
}