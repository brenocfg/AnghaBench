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
struct ass_draw {int scale; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int round (float) ; 
 int /*<<< orphan*/  talloc_asprintf_append (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void ass_draw_c(struct ass_draw *d, float x, float y)
{
    int ix = round(x * (1 << (d->scale - 1)));
    int iy = round(y * (1 << (d->scale - 1)));
    d->text = talloc_asprintf_append(d->text, " %d %d", ix, iy);
}