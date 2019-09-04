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
struct TYPE_2__ {int len; scalar_t__ val; } ;
struct property {TYPE_1__ val; } ;
typedef  int /*<<< orphan*/  fdt32_t ;
typedef  int /*<<< orphan*/  cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fdt32_to_cpu (int /*<<< orphan*/ ) ; 

cell_t propval_cell(struct property *prop)
{
	assert(prop->val.len == sizeof(cell_t));
	return fdt32_to_cpu(*((fdt32_t *)prop->val.val));
}