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
typedef  int /*<<< orphan*/  gdImagePtr ;

/* Variables and functions */
 int /*<<< orphan*/  gdAlphaOpaque ; 
 int gdImageColorAllocateAlpha (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 

int gdImageColorAllocate (gdImagePtr im, int r, int g, int b)
{
	return gdImageColorAllocateAlpha (im, r, g, b, gdAlphaOpaque);
}