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
 int TJSAMP_GRAY ; 
 int TJ_NUMSAMP ; 
 int /*<<< orphan*/  _throwg (char*) ; 
 int* tjMCUWidth ; 

int tjPlaneWidth(int componentID, int width, int subsamp)
{
	int pw, nc, retval=0;

	if(width<1 || subsamp<0 || subsamp>=TJ_NUMSAMP)
    _throwg("tjPlaneWidth(): Invalid argument");
	nc=(subsamp==TJSAMP_GRAY? 1:3);
	if(componentID<0 || componentID>=nc)
    _throwg("tjPlaneWidth(): Invalid argument");

	pw=PAD(width, tjMCUWidth[subsamp]/8);
	if(componentID==0)
		retval=pw;
	else
		retval=pw*8/tjMCUWidth[subsamp];

	bailout:
	return retval;
}