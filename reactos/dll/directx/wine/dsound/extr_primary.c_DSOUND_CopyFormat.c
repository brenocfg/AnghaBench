#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ wFormatTag; } ;
struct TYPE_9__ {int nBlockAlign; int nChannels; int wBitsPerSample; int nAvgBytesPerSec; int nSamplesPerSec; scalar_t__ cbSize; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* LPWAVEFORMATEX ;
typedef  TYPE_2__* LPCWAVEFORMATEX ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (TYPE_1__*,TYPE_2__*,int) ; 
 int DSOUND_GetFormatSize (TYPE_2__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ WAVE_FORMAT_PCM ; 

LPWAVEFORMATEX DSOUND_CopyFormat(LPCWAVEFORMATEX wfex)
{
	DWORD size = DSOUND_GetFormatSize(wfex);
	LPWAVEFORMATEX pwfx = HeapAlloc(GetProcessHeap(),0,size);
	if (pwfx == NULL) {
		WARN("out of memory\n");
	} else if (wfex->wFormatTag != WAVE_FORMAT_PCM) {
		CopyMemory(pwfx, wfex, size);
	} else {
		CopyMemory(pwfx, wfex, sizeof(PCMWAVEFORMAT));
		pwfx->cbSize=0;
		if (pwfx->nBlockAlign != pwfx->nChannels * pwfx->wBitsPerSample/8) {
			WARN("Fixing bad nBlockAlign (%u)\n", pwfx->nBlockAlign);
			pwfx->nBlockAlign  = pwfx->nChannels * pwfx->wBitsPerSample/8;
		}
		if (pwfx->nAvgBytesPerSec != pwfx->nSamplesPerSec * pwfx->nBlockAlign) {
			WARN("Fixing bad nAvgBytesPerSec (%u)\n", pwfx->nAvgBytesPerSec);
			pwfx->nAvgBytesPerSec  = pwfx->nSamplesPerSec * pwfx->nBlockAlign;
		}
	}
	return pwfx;
}