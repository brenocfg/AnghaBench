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
struct swconfig_callback {scalar_t__* nest; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
swconfig_close_portlist(struct swconfig_callback *cb, void *arg)
{
	if (cb->nest[0])
		nla_nest_end(cb->msg, cb->nest[0]);
	return 0;
}