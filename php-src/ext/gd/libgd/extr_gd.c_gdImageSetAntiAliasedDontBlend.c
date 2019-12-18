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
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_3__ {int AA; int AA_color; int AA_dont_blend; } ;

/* Variables and functions */

void gdImageSetAntiAliasedDontBlend (gdImagePtr im, int c, int dont_blend)
{
	im->AA = 1;
	im->AA_color = c;
	im->AA_dont_blend = dont_blend;
}