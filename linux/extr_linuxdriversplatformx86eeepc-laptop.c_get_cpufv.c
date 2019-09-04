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
struct eeepc_laptop {int dummy; } ;
struct eeepc_cpufv {int cur; int num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_CPUFV ; 
 int ENODEV ; 
 int get_acpi (struct eeepc_laptop*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_cpufv(struct eeepc_laptop *eeepc, struct eeepc_cpufv *c)
{
	c->cur = get_acpi(eeepc, CM_ASL_CPUFV);
	if (c->cur < 0)
		return -ENODEV;

	c->num = (c->cur >> 8) & 0xff;
	c->cur &= 0xff;
	if (c->num == 0 || c->num > 12)
		return -ENODEV;
	return 0;
}