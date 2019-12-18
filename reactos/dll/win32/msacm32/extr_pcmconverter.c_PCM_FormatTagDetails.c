#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dwFormatTagIndex; int cbFormatSize; scalar_t__* szFormatTag; int /*<<< orphan*/  cStandardFormats; int /*<<< orphan*/  fdwSupport; int /*<<< orphan*/  dwFormatTag; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMFORMATTAGDETAILSW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CONVERTER ; 
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
#define  ACM_FORMATTAGDETAILSF_FORMATTAG 130 
#define  ACM_FORMATTAGDETAILSF_INDEX 129 
#define  ACM_FORMATTAGDETAILSF_LARGESTSIZE 128 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  PCM_Formats ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  WAVE_FORMAT_UNKNOWN ; 

__attribute__((used)) static	LRESULT	PCM_FormatTagDetails(PACMFORMATTAGDETAILSW aftd, DWORD dwQuery)
{
    TRACE("(%p, %08x)\n", aftd, dwQuery);

    switch (dwQuery) {
    case ACM_FORMATTAGDETAILSF_INDEX:
	if (aftd->dwFormatTagIndex != 0) {
            WARN("not possible\n");
            return ACMERR_NOTPOSSIBLE;
        }
	break;
    case ACM_FORMATTAGDETAILSF_FORMATTAG:
	if (aftd->dwFormatTag != WAVE_FORMAT_PCM) {
            WARN("not possible\n");
            return ACMERR_NOTPOSSIBLE;
        }
	break;
    case ACM_FORMATTAGDETAILSF_LARGESTSIZE:
	if (aftd->dwFormatTag != WAVE_FORMAT_UNKNOWN &&
	    aftd->dwFormatTag != WAVE_FORMAT_PCM) {
            WARN("not possible\n");
	    return ACMERR_NOTPOSSIBLE;
        }
	break;
    default:
	WARN("Unsupported query %08x\n", dwQuery);
	return MMSYSERR_NOTSUPPORTED;
    }

    aftd->dwFormatTagIndex = 0;
    aftd->dwFormatTag = WAVE_FORMAT_PCM;
    aftd->cbFormatSize = sizeof(PCMWAVEFORMAT);
    aftd->fdwSupport = ACMDRIVERDETAILS_SUPPORTF_CONVERTER;
    aftd->cStandardFormats = ARRAY_SIZE(PCM_Formats);
    aftd->szFormatTag[0] = 0;

    return MMSYSERR_NOERROR;
}