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
 int /*<<< orphan*/  _throwg (char*) ; 
 int abs (int) ; 
 int tjPlaneHeight (int,int,int) ; 
 int tjPlaneWidth (int,int,int) ; 

unsigned long tjPlaneSizeYUV(int componentID, int width, int stride,
                                       int height, int subsamp)
{
	unsigned long retval=0;
	int pw, ph;

	if(width<1 || height<1 || subsamp<0 || subsamp>=NUMSUBOPT)
    _throwg("tjPlaneSizeYUV(): Invalid argument");

	pw=tjPlaneWidth(componentID, width, subsamp);
	ph=tjPlaneHeight(componentID, height, subsamp);
	if(pw<0 || ph<0) return -1;

	if(stride==0) stride=pw;
	else stride=abs(stride);

	retval=stride*(ph-1)+pw;

	bailout:
	return retval;
}