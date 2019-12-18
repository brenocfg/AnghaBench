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
struct srcu_struct {int dummy; } ;

/* Variables and functions */
 int init_srcu_struct_fields (struct srcu_struct*) ; 

int init_srcu_struct(struct srcu_struct *ssp)
{
	return init_srcu_struct_fields(ssp);
}