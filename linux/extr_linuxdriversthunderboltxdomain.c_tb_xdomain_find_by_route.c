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
struct tb_xdomain_lookup {int /*<<< orphan*/  route; } ;
struct tb_xdomain {int dummy; } ;
struct tb {int /*<<< orphan*/  root_switch; } ;
typedef  int /*<<< orphan*/  lookup ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tb_xdomain_lookup*,int /*<<< orphan*/ ,int) ; 
 struct tb_xdomain* switch_find_xdomain (int /*<<< orphan*/ ,struct tb_xdomain_lookup*) ; 
 struct tb_xdomain* tb_xdomain_get (struct tb_xdomain*) ; 

struct tb_xdomain *tb_xdomain_find_by_route(struct tb *tb, u64 route)
{
	struct tb_xdomain_lookup lookup;
	struct tb_xdomain *xd;

	memset(&lookup, 0, sizeof(lookup));
	lookup.route = route;

	xd = switch_find_xdomain(tb->root_switch, &lookup);
	return tb_xdomain_get(xd);
}