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
struct sti_struct {int font_width; int font_height; } ;

/* Variables and functions */
 int sti_onscreen_x (struct sti_struct*) ; 
 int sti_onscreen_y (struct sti_struct*) ; 
 int /*<<< orphan*/  sti_set (struct sti_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct sti_struct* sticon_sti ; 
 int /*<<< orphan*/  vc_resize (struct vc_data*,int,int) ; 

__attribute__((used)) static void sticon_init(struct vc_data *c, int init)
{
    struct sti_struct *sti = sticon_sti;
    int vc_cols, vc_rows;

    sti_set(sti, 0, 0, sti_onscreen_y(sti), sti_onscreen_x(sti), 0);
    vc_cols = sti_onscreen_x(sti) / sti->font_width;
    vc_rows = sti_onscreen_y(sti) / sti->font_height;
    c->vc_can_do_color = 1;
    
    if (init) {
	c->vc_cols = vc_cols;
	c->vc_rows = vc_rows;
    } else {
	/* vc_rows = (c->vc_rows > vc_rows) ? vc_rows : c->vc_rows; */
	/* vc_cols = (c->vc_cols > vc_cols) ? vc_cols : c->vc_cols; */
	vc_resize(c, vc_cols, vc_rows);
/*	vc_resize_con(vc_rows, vc_cols, c->vc_num); */
    }
}