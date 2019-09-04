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
struct nk_color {int r; int g; int b; } ;
struct TYPE_3__ {int Red; int Green; int Blue; int Alpha; } ;
typedef  TYPE_1__* PTRIVERTEX ;

/* Variables and functions */

__attribute__((used)) static void
nk_gdi_set_vertexColor(PTRIVERTEX tri, struct nk_color col)
{
    tri->Red   = col.r << 8;
    tri->Green = col.g << 8;
    tri->Blue  = col.b << 8;
    tri->Alpha = 0xff << 8;
}