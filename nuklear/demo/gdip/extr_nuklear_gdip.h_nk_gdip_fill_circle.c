#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nk_color {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  brush; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  GdipFillEllipseI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  GdipSetSolidFillColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_color (struct nk_color) ; 
 TYPE_1__ gdip ; 

__attribute__((used)) static void
nk_gdip_fill_circle(short x, short y, unsigned short w,
    unsigned short h, struct nk_color col)
{
    GdipSetSolidFillColor(gdip.brush, convert_color(col));
    GdipFillEllipseI(gdip.memory, gdip.brush, x, y, w, h);
}