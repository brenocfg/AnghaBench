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
struct ass_draw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ass_draw_append (struct ass_draw*,char*) ; 
 int /*<<< orphan*/  ass_draw_c (struct ass_draw*,float,float) ; 

__attribute__((used)) static void ass_draw_line_to(struct ass_draw *d, float x, float y)
{
    ass_draw_append(d, " l");
    ass_draw_c(d, x, y);
}