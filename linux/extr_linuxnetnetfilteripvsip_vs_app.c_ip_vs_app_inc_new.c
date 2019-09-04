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
struct netns_ipvs {int dummy; } ;
struct ip_vs_protocol {int (* register_app ) (struct netns_ipvs*,struct ip_vs_app*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  unregister_app; } ;
struct ip_vs_app {int /*<<< orphan*/  port; int /*<<< orphan*/  name; int /*<<< orphan*/  incs_list; int /*<<< orphan*/  a_list; int /*<<< orphan*/  timeout_table; int /*<<< orphan*/  timeouts_size; scalar_t__ timeouts; int /*<<< orphan*/  usecnt; struct ip_vs_app* app; int /*<<< orphan*/  p_list; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_app_inc_destroy (struct ip_vs_app*) ; 
 int /*<<< orphan*/  ip_vs_create_timeout_table (scalar_t__,int /*<<< orphan*/ ) ; 
 struct ip_vs_protocol* ip_vs_proto_get (int /*<<< orphan*/ ) ; 
 struct ip_vs_app* kmemdup (struct ip_vs_app*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int stub1 (struct netns_ipvs*,struct ip_vs_app*) ; 

__attribute__((used)) static int
ip_vs_app_inc_new(struct netns_ipvs *ipvs, struct ip_vs_app *app, __u16 proto,
		  __u16 port)
{
	struct ip_vs_protocol *pp;
	struct ip_vs_app *inc;
	int ret;

	if (!(pp = ip_vs_proto_get(proto)))
		return -EPROTONOSUPPORT;

	if (!pp->unregister_app)
		return -EOPNOTSUPP;

	inc = kmemdup(app, sizeof(*inc), GFP_KERNEL);
	if (!inc)
		return -ENOMEM;
	INIT_LIST_HEAD(&inc->p_list);
	INIT_LIST_HEAD(&inc->incs_list);
	inc->app = app;
	inc->port = htons(port);
	atomic_set(&inc->usecnt, 0);

	if (app->timeouts) {
		inc->timeout_table =
			ip_vs_create_timeout_table(app->timeouts,
						   app->timeouts_size);
		if (!inc->timeout_table) {
			ret = -ENOMEM;
			goto out;
		}
	}

	ret = pp->register_app(ipvs, inc);
	if (ret)
		goto out;

	list_add(&inc->a_list, &app->incs_list);
	IP_VS_DBG(9, "%s App %s:%u registered\n",
		  pp->name, inc->name, ntohs(inc->port));

	return 0;

  out:
	ip_vs_app_inc_destroy(inc);
	return ret;
}