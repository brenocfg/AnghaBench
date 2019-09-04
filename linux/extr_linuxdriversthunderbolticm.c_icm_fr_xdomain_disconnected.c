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
struct tb_xdomain {int dummy; } ;
struct tb {int dummy; } ;
struct icm_pkg_header {int dummy; } ;
struct icm_fr_event_xdomain_disconnected {int /*<<< orphan*/  remote_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_xdomain (struct tb_xdomain*) ; 
 struct tb_xdomain* tb_xdomain_find_by_uuid (struct tb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_xdomain_put (struct tb_xdomain*) ; 

__attribute__((used)) static void
icm_fr_xdomain_disconnected(struct tb *tb, const struct icm_pkg_header *hdr)
{
	const struct icm_fr_event_xdomain_disconnected *pkg =
		(const struct icm_fr_event_xdomain_disconnected *)hdr;
	struct tb_xdomain *xd;

	/*
	 * If the connection is through one or multiple devices, the
	 * XDomain device is removed along with them so it is fine if we
	 * cannot find it here.
	 */
	xd = tb_xdomain_find_by_uuid(tb, &pkg->remote_uuid);
	if (xd) {
		remove_xdomain(xd);
		tb_xdomain_put(xd);
	}
}