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
 int* tjMCUHeight ; 
 int* tjMCUWidth ; 

unsigned long tjBufSize(int width, int height, int jpegSubsamp)
{
  unsigned long retval = 0;
  int mcuw, mcuh, chromasf;

	if(width<1 || height<1 || jpegSubsamp<0 || jpegSubsamp>=NUMSUBOPT)
    _throwg("tjBufSize(): Invalid argument");

	/* This allows for rare corner cases in which a JPEG image can actually be
	   larger than the uncompressed input (we wouldn't mention it if it hadn't
	   happened before.) */
	mcuw=tjMCUWidth[jpegSubsamp];
	mcuh=tjMCUHeight[jpegSubsamp];
	chromasf=jpegSubsamp==TJSAMP_GRAY? 0: 4*64/(mcuw*mcuh);
	retval=PAD(width, mcuw) * PAD(height, mcuh) * (2 + chromasf) + 2048;

	bailout:
	return retval;
}