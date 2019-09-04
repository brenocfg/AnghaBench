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
typedef  int u64 ;
struct TYPE_2__ {int route_lo; scalar_t__ route_hi; } ;
struct tb_switch {TYPE_1__ config; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 tb_route(struct tb_switch *sw)
{
	return ((u64) sw->config.route_hi) << 32 | sw->config.route_lo;
}