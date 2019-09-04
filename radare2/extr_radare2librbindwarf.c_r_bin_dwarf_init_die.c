#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int capacity; scalar_t__ length; int /*<<< orphan*/  attr_values; } ;
typedef  TYPE_1__ RBinDwarfDIE ;
typedef  int /*<<< orphan*/  RBinDwarfAttrValue ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  calloc (int,int) ; 

__attribute__((used)) static int r_bin_dwarf_init_die(RBinDwarfDIE *die) {
	if (!die) {
		return -EINVAL;
	}
	die->attr_values = calloc (sizeof (RBinDwarfAttrValue), 8);
	if (!die->attr_values) {
		return -ENOMEM;
	}
	die->capacity = 8;
	die->length = 0;
	return 0;
}