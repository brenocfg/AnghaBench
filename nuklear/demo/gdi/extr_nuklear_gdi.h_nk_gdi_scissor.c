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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  IntersectClipRect (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  SelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nk_gdi_scissor(HDC dc, float x, float y, float w, float h)
{
    SelectClipRgn(dc, NULL);
    IntersectClipRect(dc, (int)x, (int)y, (int)(x + w + 1), (int)(y + h + 1));
}