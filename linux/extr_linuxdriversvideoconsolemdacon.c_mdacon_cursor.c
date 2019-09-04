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
struct vc_data {int vc_y; int vc_x; int vc_cursor_type; } ;

/* Variables and functions */
 int CM_ERASE ; 
#define  CUR_BLOCK 132 
#define  CUR_LOWER_HALF 131 
#define  CUR_LOWER_THIRD 130 
#define  CUR_NONE 129 
#define  CUR_TWO_THIRDS 128 
 int mda_num_columns ; 
 int /*<<< orphan*/  mda_set_cursor (int) ; 
 int /*<<< orphan*/  mda_set_cursor_size (int,int) ; 
 int mda_vram_len ; 

__attribute__((used)) static void mdacon_cursor(struct vc_data *c, int mode)
{
	if (mode == CM_ERASE) {
		mda_set_cursor(mda_vram_len - 1);
		return;
	}

	mda_set_cursor(c->vc_y*mda_num_columns*2 + c->vc_x*2);

	switch (c->vc_cursor_type & 0x0f) {

		case CUR_LOWER_THIRD:	mda_set_cursor_size(10, 13); break;
		case CUR_LOWER_HALF:	mda_set_cursor_size(7,  13); break;
		case CUR_TWO_THIRDS:	mda_set_cursor_size(4,  13); break;
		case CUR_BLOCK:		mda_set_cursor_size(1,  13); break;
		case CUR_NONE:		mda_set_cursor_size(14, 13); break;
		default:		mda_set_cursor_size(12, 13); break;
	}
}