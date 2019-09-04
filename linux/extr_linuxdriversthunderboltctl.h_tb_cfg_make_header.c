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
typedef  int u64 ;
struct tb_cfg_header {int route_hi; int route_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int tb_cfg_get_route (struct tb_cfg_header*) ; 

__attribute__((used)) static inline struct tb_cfg_header tb_cfg_make_header(u64 route)
{
	struct tb_cfg_header header = {
		.route_hi = route >> 32,
		.route_lo = route,
	};
	/* check for overflow, route_hi is not 32 bits! */
	WARN_ON(tb_cfg_get_route(&header) != route);
	return header;
}