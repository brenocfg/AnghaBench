#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  string; } ;
struct TYPE_8__ {TYPE_2__ block; TYPE_1__ str_struct; } ;
struct TYPE_9__ {int form; TYPE_3__ encoding; } ;
typedef  TYPE_4__ RBinDwarfAttrValue ;

/* Variables and functions */
#define  DW_FORM_block 133 
#define  DW_FORM_block1 132 
#define  DW_FORM_block2 131 
#define  DW_FORM_block4 130 
#define  DW_FORM_string 129 
#define  DW_FORM_strp 128 
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_bin_dwarf_free_attr_value(RBinDwarfAttrValue *val) {
	if (!val) {
		return;
	}
	switch (val->form) {
	case DW_FORM_strp:
	case DW_FORM_string:
		R_FREE (val->encoding.str_struct.string);
		break;
	case DW_FORM_block:
	case DW_FORM_block1:
	case DW_FORM_block2:
	case DW_FORM_block4:
		R_FREE (val->encoding.block.data);
		break;
	default:
		break;
	};
}