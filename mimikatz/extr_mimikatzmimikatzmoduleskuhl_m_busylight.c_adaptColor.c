#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int member_0; int member_1; int member_2; int red; int green; int blue; } ;
struct TYPE_5__ {scalar_t__ blue; scalar_t__ green; scalar_t__ red; } ;
typedef  TYPE_1__* PCBUSYLIGHT_COLOR ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  TYPE_2__ BUSYLIGHT_COLOR ;

/* Variables and functions */

BUSYLIGHT_COLOR adaptColor(PCBUSYLIGHT_COLOR color, BYTE percent)
{
	BUSYLIGHT_COLOR rColor = {
		(BYTE) (((DWORD) color->red * percent) / 100),
		(BYTE) (((DWORD) color->green * percent) / 100),
		(BYTE) (((DWORD) color->blue * percent) / 100)
	};
	if(!rColor.red && percent && color->red)
		rColor.red = 1;
	if(!rColor.green && percent && color->green)
		rColor.green = 1;
	if(!rColor.blue && percent && color->blue)
		rColor.blue = 1;
	return rColor;
}