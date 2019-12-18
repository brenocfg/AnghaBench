#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_3__ {int dwFormatTagIndex; int dwFormatTag; int cbFormatSize; int /*<<< orphan*/  szFormatTag; int /*<<< orphan*/  cStandardFormats; int /*<<< orphan*/  fdwSupport; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMFORMATTAGDETAILSW ;
typedef  int /*<<< orphan*/  MPEGLAYER3WAVEFORMAT ;
typedef  int /*<<< orphan*/  MPEG1WAVEFORMAT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CODEC ; 
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
#define  ACM_FORMATTAGDETAILSF_FORMATTAG 133 
#define  ACM_FORMATTAGDETAILSF_INDEX 132 
#define  ACM_FORMATTAGDETAILSF_LARGESTSIZE 131 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  NUM_PCM_FORMATS ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
#define  WAVE_FORMAT_MPEG 130 
#define  WAVE_FORMAT_MPEGLAYER3 129 
#define  WAVE_FORMAT_PCM 128 
 int WAVE_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static	LRESULT	MPEG3_FormatTagDetails(PACMFORMATTAGDETAILSW aftd, DWORD dwQuery)
{
    static const WCHAR szPcm[]={'P','C','M',0};
    static const WCHAR szMpeg3[]={'M','P','e','g','3',0};
    static const WCHAR szMpeg[]={'M','P','e','g',0};

    switch (dwQuery)
    {
    case ACM_FORMATTAGDETAILSF_INDEX:
	if (aftd->dwFormatTagIndex > 2) return ACMERR_NOTPOSSIBLE;
	break;
    case ACM_FORMATTAGDETAILSF_LARGESTSIZE:
	if (aftd->dwFormatTag == WAVE_FORMAT_UNKNOWN)
        {
            aftd->dwFormatTagIndex = 2; /* WAVE_FORMAT_MPEG is biggest */
	    break;
	}
	/* fall through */
    case ACM_FORMATTAGDETAILSF_FORMATTAG:
	switch (aftd->dwFormatTag)
        {
	case WAVE_FORMAT_PCM:		aftd->dwFormatTagIndex = 0; break;
	case WAVE_FORMAT_MPEGLAYER3:    aftd->dwFormatTagIndex = 1; break;
	case WAVE_FORMAT_MPEG:          aftd->dwFormatTagIndex = 2; break;
	default:			return ACMERR_NOTPOSSIBLE;
	}
	break;
    default:
	WARN("Unsupported query %08x\n", dwQuery);
	return MMSYSERR_NOTSUPPORTED;
    }

    aftd->fdwSupport = ACMDRIVERDETAILS_SUPPORTF_CODEC;
    switch (aftd->dwFormatTagIndex)
    {
    case 0:
	aftd->dwFormatTag = WAVE_FORMAT_PCM;
	aftd->cbFormatSize = sizeof(PCMWAVEFORMAT);
	aftd->cStandardFormats = NUM_PCM_FORMATS;
        lstrcpyW(aftd->szFormatTag, szPcm);
        break;
    case 1:
	aftd->dwFormatTag = WAVE_FORMAT_MPEGLAYER3;
	aftd->cbFormatSize = sizeof(MPEGLAYER3WAVEFORMAT);
        aftd->cStandardFormats = 0;
        lstrcpyW(aftd->szFormatTag, szMpeg3);
	break;
    case 2:
	aftd->dwFormatTag = WAVE_FORMAT_MPEG;
	aftd->cbFormatSize = sizeof(MPEG1WAVEFORMAT);
        aftd->cStandardFormats = 0;
        lstrcpyW(aftd->szFormatTag, szMpeg);
	break;
    }
    return MMSYSERR_NOERROR;
}