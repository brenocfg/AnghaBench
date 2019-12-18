#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cksize; } ;
struct TYPE_8__ {int dwMciTimeFormat; TYPE_2__* lpWaveFormat; TYPE_1__ ckWaveData; } ;
typedef  TYPE_3__ WINE_MCIWAVE ;
struct TYPE_7__ {int nSamplesPerSec; int /*<<< orphan*/  nAvgBytesPerSec; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
#define  MCI_FORMAT_BYTES 130 
#define  MCI_FORMAT_MILLISECONDS 129 
#define  MCI_FORMAT_SAMPLES 128 
 int /*<<< orphan*/  MulDiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  WAVE_ConvertByteToTimeFormat (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	DWORD 	WAVE_ConvertTimeFormatToByte(WINE_MCIWAVE* wmw, DWORD val)
{
    DWORD	ret = 0;

    switch (wmw->dwMciTimeFormat) {
    case MCI_FORMAT_MILLISECONDS:
	ret = MulDiv(val,wmw->lpWaveFormat->nAvgBytesPerSec,1000);
	if (ret > wmw->ckWaveData.cksize &&
	    val == WAVE_ConvertByteToTimeFormat(wmw, wmw->ckWaveData.cksize))
	    ret = wmw->ckWaveData.cksize;
	break;
    case MCI_FORMAT_BYTES:
	ret = val;
	break;
    case MCI_FORMAT_SAMPLES:
	ret = MulDiv(val,wmw->lpWaveFormat->nAvgBytesPerSec,wmw->lpWaveFormat->nSamplesPerSec);
	break;
    default:
	WARN("Bad time format %u!\n", wmw->dwMciTimeFormat);
    }
    TRACE("val=%u=0x%08x [tf=%u] => ret=%u\n", val, val, wmw->dwMciTimeFormat, ret);
    return ret;
}