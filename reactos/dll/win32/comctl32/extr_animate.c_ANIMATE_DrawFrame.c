#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ (* fnICDecompress ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dwSuggestedBufferSize; } ;
struct TYPE_8__ {size_t currFrame; int nLoop; size_t nFromFrame; int /*<<< orphan*/  nToFrame; int /*<<< orphan*/  outdata; int /*<<< orphan*/  outbih; int /*<<< orphan*/  indata; int /*<<< orphan*/  inbih; scalar_t__ hic; TYPE_1__ ash; int /*<<< orphan*/  hMMio; int /*<<< orphan*/ * lpIndex; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ ANIMATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ANIMATE_DoStop (TYPE_2__*) ; 
 int /*<<< orphan*/  ANIMATE_PaintFrame (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ICERR_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRACE (char*,size_t,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 TYPE_3__ fnIC ; 
 int /*<<< orphan*/  mmioRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmioSeek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL ANIMATE_DrawFrame(ANIMATE_INFO *infoPtr, HDC hDC)
{
    TRACE("Drawing frame %d (loop %d)\n", infoPtr->currFrame, infoPtr->nLoop);

    mmioSeek(infoPtr->hMMio, infoPtr->lpIndex[infoPtr->currFrame], SEEK_SET);
    mmioRead(infoPtr->hMMio, infoPtr->indata, infoPtr->ash.dwSuggestedBufferSize);

    if (infoPtr->hic &&
	fnIC.fnICDecompress(infoPtr->hic, 0, infoPtr->inbih, infoPtr->indata,
		     infoPtr->outbih, infoPtr->outdata) != ICERR_OK) {
	WARN("Decompression error\n");
	return FALSE;
    }

    ANIMATE_PaintFrame(infoPtr, hDC);

    if (infoPtr->currFrame++ >= infoPtr->nToFrame) {
	infoPtr->currFrame = infoPtr->nFromFrame;
	if (infoPtr->nLoop != -1) {
	    if (--infoPtr->nLoop == 0) {
		ANIMATE_DoStop(infoPtr);
	    }
	}
    }

    return TRUE;
}