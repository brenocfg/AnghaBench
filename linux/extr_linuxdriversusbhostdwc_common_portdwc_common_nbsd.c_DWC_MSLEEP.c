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
typedef  int uint32_t ;
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  tsleep (struct timeval*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

void DWC_MSLEEP(uint32_t msecs)
{
	struct timeval tv;

	tv.tv_sec = msecs / 1000;
	tv.tv_usec = (msecs - tv.tv_sec * 1000) * 1000;
	tsleep(&tv, 0, "dw3slp", tvtohz(&tv));
}