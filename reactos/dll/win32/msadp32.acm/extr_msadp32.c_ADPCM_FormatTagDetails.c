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
struct TYPE_3__ {int dwFormatTagIndex; int dwFormatTag; int cbFormatSize; int /*<<< orphan*/  szFormatTag; void* cStandardFormats; int /*<<< orphan*/  fdwSupport; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMFORMATTAGDETAILSW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  ADPCMWAVEFORMAT ;
typedef  int /*<<< orphan*/  ADPCMCOEFSET ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CODEC ; 
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
#define  ACM_FORMATTAGDETAILSF_FORMATTAG 132 
#define  ACM_FORMATTAGDETAILSF_INDEX 131 
#define  ACM_FORMATTAGDETAILSF_LARGESTSIZE 130 
 int /*<<< orphan*/  ADPCM_Formats ; 
 void* ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  PCM_Formats ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
#define  WAVE_FORMAT_ADPCM 129 
#define  WAVE_FORMAT_PCM 128 
 int WAVE_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static	LRESULT	ADPCM_FormatTagDetails(PACMFORMATTAGDETAILSW aftd, DWORD dwQuery)
{
    static const WCHAR szPcm[]={'P','C','M',0};
    static const WCHAR szMsAdPcm[]={'M','i','c','r','o','s','o','f','t',' ','A','D','P','C','M',0};

    switch (dwQuery)
    {
    case ACM_FORMATTAGDETAILSF_INDEX:
	if (aftd->dwFormatTagIndex >= 2) return ACMERR_NOTPOSSIBLE;
	break;
    case ACM_FORMATTAGDETAILSF_LARGESTSIZE:
	if (aftd->dwFormatTag == WAVE_FORMAT_UNKNOWN)
        {
            aftd->dwFormatTagIndex = 1; /* WAVE_FORMAT_ADPCM is bigger than PCM */
	    break;
	}
	/* fall through */
    case ACM_FORMATTAGDETAILSF_FORMATTAG:
	switch (aftd->dwFormatTag)
        {
	case WAVE_FORMAT_PCM:	aftd->dwFormatTagIndex = 0; break;
	case WAVE_FORMAT_ADPCM: aftd->dwFormatTagIndex = 1; break;
	default:		return ACMERR_NOTPOSSIBLE;
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
	aftd->cStandardFormats = ARRAY_SIZE(PCM_Formats);
        lstrcpyW(aftd->szFormatTag, szPcm);
        break;
    case 1:
	aftd->dwFormatTag = WAVE_FORMAT_ADPCM;
	aftd->cbFormatSize = sizeof(ADPCMWAVEFORMAT) + (7 - 1) * sizeof(ADPCMCOEFSET);
	aftd->cStandardFormats = ARRAY_SIZE(ADPCM_Formats);
        lstrcpyW(aftd->szFormatTag, szMsAdPcm);
	break;
    }
    return MMSYSERR_NOERROR;
}