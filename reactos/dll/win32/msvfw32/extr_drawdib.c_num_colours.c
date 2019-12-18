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
struct TYPE_3__ {int biClrUsed; int biBitCount; } ;
typedef  TYPE_1__ BITMAPINFOHEADER ;

/* Variables and functions */

__attribute__((used)) static int num_colours(const BITMAPINFOHEADER *lpbi)
{
	if(lpbi->biClrUsed)
		return lpbi->biClrUsed;
	if(lpbi->biBitCount<=8)
		return 1<<lpbi->biBitCount;
	return 0;
}