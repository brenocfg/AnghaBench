#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fccIOProc; int dwFlags; scalar_t__ pchBuffer; scalar_t__ pchEndRead; scalar_t__ pchNext; int /*<<< orphan*/  lBufOffset; scalar_t__ cchBuffer; } ;
struct TYPE_4__ {TYPE_2__ info; int /*<<< orphan*/  ioProc; } ;
typedef  TYPE_1__ WINE_MMIO ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FOURCC_MEM ; 
 int /*<<< orphan*/  MMIOM_SEEK ; 
 int /*<<< orphan*/  MMIOM_WRITE ; 
 int MMIO_DIRTY ; 
 int MMIO_EMPTYBUF ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 scalar_t__ SEEK_SET ; 
 int /*<<< orphan*/  send_message (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	MMRESULT MMIO_Flush(WINE_MMIO* wm, UINT uFlags)
{
    if (wm->info.cchBuffer && (wm->info.fccIOProc != FOURCC_MEM)) {
	/* not quite sure what to do here, but I'll guess */
	if (wm->info.dwFlags & MMIO_DIRTY) {
            /* FIXME: error handling */
	    send_message(wm->ioProc, &wm->info, MMIOM_SEEK, wm->info.lBufOffset, SEEK_SET, FALSE);
	    send_message(wm->ioProc, &wm->info, MMIOM_WRITE,
                         (LPARAM)wm->info.pchBuffer,
                         wm->info.pchNext - wm->info.pchBuffer, FALSE);
	}
	if (uFlags & MMIO_EMPTYBUF)
	    wm->info.pchNext = wm->info.pchEndRead = wm->info.pchBuffer;
    }
    wm->info.dwFlags &= ~MMIO_DIRTY;

    return MMSYSERR_NOERROR;
}