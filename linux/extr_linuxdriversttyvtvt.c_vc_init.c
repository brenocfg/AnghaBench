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
struct vc_data {unsigned int vc_cols; unsigned int vc_rows; unsigned int vc_size_row; int vc_screenbuf_size; int vc_halfcolor; int /*<<< orphan*/  paste_wait; int /*<<< orphan*/  vc_itcolor; int /*<<< orphan*/  vc_ulcolor; int /*<<< orphan*/  vc_def_color; int /*<<< orphan*/ * vc_palette; int /*<<< orphan*/  vc_origin; int /*<<< orphan*/  vc_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/ * default_blu ; 
 int /*<<< orphan*/  default_color ; 
 int /*<<< orphan*/ * default_grn ; 
 int /*<<< orphan*/  default_italic_color ; 
 int /*<<< orphan*/ * default_red ; 
 int /*<<< orphan*/  default_underline_color ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_terminal (struct vc_data*,int) ; 
 int /*<<< orphan*/  reset_vc (struct vc_data*) ; 
 int /*<<< orphan*/  set_origin (struct vc_data*) ; 

__attribute__((used)) static void vc_init(struct vc_data *vc, unsigned int rows,
		    unsigned int cols, int do_clear)
{
	int j, k ;

	vc->vc_cols = cols;
	vc->vc_rows = rows;
	vc->vc_size_row = cols << 1;
	vc->vc_screenbuf_size = vc->vc_rows * vc->vc_size_row;

	set_origin(vc);
	vc->vc_pos = vc->vc_origin;
	reset_vc(vc);
	for (j=k=0; j<16; j++) {
		vc->vc_palette[k++] = default_red[j] ;
		vc->vc_palette[k++] = default_grn[j] ;
		vc->vc_palette[k++] = default_blu[j] ;
	}
	vc->vc_def_color       = default_color;
	vc->vc_ulcolor         = default_underline_color;
	vc->vc_itcolor         = default_italic_color;
	vc->vc_halfcolor       = 0x08;   /* grey */
	init_waitqueue_head(&vc->paste_wait);
	reset_terminal(vc, do_clear);
}