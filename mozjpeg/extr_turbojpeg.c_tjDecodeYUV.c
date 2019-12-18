#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  isInstanceError; } ;
typedef  TYPE_1__ tjinstance ;
typedef  scalar_t__ tjhandle ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int NUMSUBOPT ; 
 int PAD (int,int) ; 
 int TJSAMP_GRAY ; 
 int /*<<< orphan*/  _throw (char*) ; 
 int /*<<< orphan*/  _throwg (char*) ; 
 int /*<<< orphan*/  isPow2 (int) ; 
 int tjDecodeYUVPlanes (scalar_t__,unsigned char const**,int*,int,unsigned char*,int,int,int,int,int) ; 
 int tjPlaneHeight (int,int,int) ; 
 int tjPlaneWidth (int,int,int) ; 

int tjDecodeYUV(tjhandle handle, const unsigned char *srcBuf,
                          int pad, int subsamp, unsigned char *dstBuf,
                          int width, int pitch, int height, int pixelFormat,
                          int flags)
{
	const unsigned char *srcPlanes[3];
	int pw0, ph0, strides[3], retval=-1;
  tjinstance *this = (tjinstance *)handle;

  if (!this) _throwg("tjDecodeYUV(): Invalid handle");
  this->isInstanceError = FALSE;

  if (srcBuf == NULL || pad < 0 || !isPow2(pad) || subsamp < 0 ||
      subsamp >= NUMSUBOPT || width <= 0 || height <= 0)
		_throw("tjDecodeYUV(): Invalid argument");

	pw0=tjPlaneWidth(0, width, subsamp);
	ph0=tjPlaneHeight(0, height, subsamp);
	srcPlanes[0]=srcBuf;
	strides[0]=PAD(pw0, pad);
  if (subsamp == TJSAMP_GRAY) {
		strides[1]=strides[2]=0;
		srcPlanes[1]=srcPlanes[2]=NULL;
  } else {
		int pw1=tjPlaneWidth(1, width, subsamp);
		int ph1=tjPlaneHeight(1, height, subsamp);

		strides[1]=strides[2]=PAD(pw1, pad);
		srcPlanes[1]=srcPlanes[0]+strides[0]*ph0;
		srcPlanes[2]=srcPlanes[1]+strides[1]*ph1;
	}

	return tjDecodeYUVPlanes(handle, srcPlanes, strides, subsamp, dstBuf, width,
		pitch, height, pixelFormat, flags);

	bailout:
	return retval;
}