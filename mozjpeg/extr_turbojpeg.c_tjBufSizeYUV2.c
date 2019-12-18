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
 int NUMSUBOPT ; 
 int PAD (int,int) ; 
 int TJSAMP_GRAY ; 
 int /*<<< orphan*/  _throwg (char*) ; 
 int tjPlaneHeight (int,int,int) ; 
 int tjPlaneWidth (int,int,int) ; 

unsigned long tjBufSizeYUV2(int width, int pad, int height,
	int subsamp)
{
	int retval=0, nc, i;

	if(subsamp<0 || subsamp>=NUMSUBOPT)
    _throwg("tjBufSizeYUV2(): Invalid argument");

	nc=(subsamp==TJSAMP_GRAY? 1:3);
  for (i = 0; i < nc; i++) {
		int pw=tjPlaneWidth(i, width, subsamp);
		int stride=PAD(pw, pad);
		int ph=tjPlaneHeight(i, height, subsamp);

		if(pw<0 || ph<0) return -1;
		else retval+=stride*ph;
	}

	bailout:
	return retval;
}