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
struct vc_data {int vc_can_do_color; int vc_cols; int vc_rows; } ;

/* Variables and functions */
 int newport_xsize ; 
 int newport_ysize ; 
 int /*<<< orphan*/  vc_resize (struct vc_data*,int,int) ; 

__attribute__((used)) static void newport_init(struct vc_data *vc, int init)
{
	int cols, rows;

	cols = newport_xsize / 8;
	rows = newport_ysize / 16;
	vc->vc_can_do_color = 1;
	if (init) {
		vc->vc_cols = cols;
		vc->vc_rows = rows;
	} else
		vc_resize(vc, cols, rows);
}