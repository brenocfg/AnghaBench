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
struct ip_vs_proto_data {int /*<<< orphan*/  appcnt; } ;
struct ip_vs_app {int /*<<< orphan*/  p_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct ip_vs_proto_data* ip_vs_proto_data_get (struct netns_ipvs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
udp_unregister_app(struct netns_ipvs *ipvs, struct ip_vs_app *inc)
{
	struct ip_vs_proto_data *pd = ip_vs_proto_data_get(ipvs, IPPROTO_UDP);

	atomic_dec(&pd->appcnt);
	list_del_rcu(&inc->p_list);
}