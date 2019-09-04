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
typedef  int /*<<< orphan*/  u64 ;
struct tb_xdomain {int dummy; } ;
struct tb {int dummy; } ;
struct icm_tr_event_xdomain_disconnected {int /*<<< orphan*/  route_lo; int /*<<< orphan*/  route_hi; } ;
struct icm_pkg_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_route (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_xdomain (struct tb_xdomain*) ; 
 struct tb_xdomain* tb_xdomain_find_by_route (struct tb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_xdomain_put (struct tb_xdomain*) ; 

__attribute__((used)) static void
icm_tr_xdomain_disconnected(struct tb *tb, const struct icm_pkg_header *hdr)
{
	const struct icm_tr_event_xdomain_disconnected *pkg =
		(const struct icm_tr_event_xdomain_disconnected *)hdr;
	struct tb_xdomain *xd;
	u64 route;

	route = get_route(pkg->route_hi, pkg->route_lo);

	xd = tb_xdomain_find_by_route(tb, route);
	if (xd) {
		remove_xdomain(xd);
		tb_xdomain_put(xd);
	}
}