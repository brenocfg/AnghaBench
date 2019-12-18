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

/* Variables and functions */
 int PAD (int,int) ; 
 int /*<<< orphan*/  _throwg (char*) ; 

unsigned long TJBUFSIZE(int width, int height)
{
	unsigned long retval=0;

	if(width<1 || height<1)
    _throwg("TJBUFSIZE(): Invalid argument");

	/* This allows for rare corner cases in which a JPEG image can actually be
	   larger than the uncompressed input (we wouldn't mention it if it hadn't
	   happened before.) */
	retval=PAD(width, 16) * PAD(height, 16) * 6 + 2048;

	bailout:
	return retval;
}