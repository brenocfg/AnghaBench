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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct rtable {TYPE_1__ dst; } ;
struct neighbour {int dummy; } ;
struct clip_vcc {struct atmarp_entry* entry; } ;
struct atmarp_entry {int dummy; } ;
struct atm_vcc {scalar_t__ push; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct clip_vcc* CLIP_VCC (struct atm_vcc*) ; 
 int EBADF ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int NEIGH_UPDATE_F_ADMIN ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 int /*<<< orphan*/  NUD_PERMANENT ; 
 int PTR_ERR (struct rtable*) ; 
 struct neighbour* __neigh_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arp_tbl ; 
 scalar_t__ clip_push ; 
 int /*<<< orphan*/  init_net ; 
 struct rtable* ip_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  link_vcc (struct clip_vcc*,struct atmarp_entry*) ; 
 int /*<<< orphan*/  llc_oui ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int neigh_update (struct neighbour*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct atmarp_entry* neighbour_priv (struct neighbour*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  unlink_clip_vcc (struct clip_vcc*) ; 

__attribute__((used)) static int clip_setentry(struct atm_vcc *vcc, __be32 ip)
{
	struct neighbour *neigh;
	struct atmarp_entry *entry;
	int error;
	struct clip_vcc *clip_vcc;
	struct rtable *rt;

	if (vcc->push != clip_push) {
		pr_warn("non-CLIP VCC\n");
		return -EBADF;
	}
	clip_vcc = CLIP_VCC(vcc);
	if (!ip) {
		if (!clip_vcc->entry) {
			pr_err("hiding hidden ATMARP entry\n");
			return 0;
		}
		pr_debug("remove\n");
		unlink_clip_vcc(clip_vcc);
		return 0;
	}
	rt = ip_route_output(&init_net, ip, 0, 1, 0);
	if (IS_ERR(rt))
		return PTR_ERR(rt);
	neigh = __neigh_lookup(&arp_tbl, &ip, rt->dst.dev, 1);
	ip_rt_put(rt);
	if (!neigh)
		return -ENOMEM;
	entry = neighbour_priv(neigh);
	if (entry != clip_vcc->entry) {
		if (!clip_vcc->entry)
			pr_debug("add\n");
		else {
			pr_debug("update\n");
			unlink_clip_vcc(clip_vcc);
		}
		link_vcc(clip_vcc, entry);
	}
	error = neigh_update(neigh, llc_oui, NUD_PERMANENT,
			     NEIGH_UPDATE_F_OVERRIDE | NEIGH_UPDATE_F_ADMIN, 0);
	neigh_release(neigh);
	return error;
}