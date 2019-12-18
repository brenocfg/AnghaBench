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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int vdwACM; int vdwDriver; int cFormatTags; scalar_t__* szFeatures; int /*<<< orphan*/  szLicensing; int /*<<< orphan*/  szCopyright; int /*<<< orphan*/  szLongName; int /*<<< orphan*/  szShortName; int /*<<< orphan*/ * hicon; scalar_t__ cFilterTags; int /*<<< orphan*/  fdwSupport; int /*<<< orphan*/  wPid; int /*<<< orphan*/  wMid; int /*<<< orphan*/  fccComp; int /*<<< orphan*/  fccType; } ;
typedef  TYPE_1__* PACMDRIVERDETAILSW ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_FCCCOMP_UNDEFINED ; 
 int /*<<< orphan*/  ACMDRIVERDETAILS_FCCTYPE_AUDIOCODEC ; 
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CODEC ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MM_FHGIIS_MPEGLAYER3_DECODE ; 
 int /*<<< orphan*/  MM_FRAUNHOFER_IIS ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static	LRESULT MPEG3_DriverDetails(PACMDRIVERDETAILSW add)
{
    add->fccType = ACMDRIVERDETAILS_FCCTYPE_AUDIOCODEC;
    add->fccComp = ACMDRIVERDETAILS_FCCCOMP_UNDEFINED;
    add->wMid = MM_FRAUNHOFER_IIS;
    add->wPid = MM_FHGIIS_MPEGLAYER3_DECODE;
    add->vdwACM = 0x01000000;
    add->vdwDriver = 0x01000000;
    add->fdwSupport = ACMDRIVERDETAILS_SUPPORTF_CODEC;
    add->cFormatTags = 3; /* PCM, MPEG3 */
    add->cFilterTags = 0;
    add->hicon = NULL;
    MultiByteToWideChar( CP_ACP, 0, "MPEG Layer-3 Codec", -1,
                         add->szShortName, sizeof(add->szShortName)/sizeof(WCHAR) );
    MultiByteToWideChar( CP_ACP, 0, "Wine MPEG3 decoder", -1,
                         add->szLongName, sizeof(add->szLongName)/sizeof(WCHAR) );
    MultiByteToWideChar( CP_ACP, 0, "Brought to you by the Wine team...", -1,
                         add->szCopyright, sizeof(add->szCopyright)/sizeof(WCHAR) );
    MultiByteToWideChar( CP_ACP, 0, "Refer to LICENSE file", -1,
                         add->szLicensing, sizeof(add->szLicensing)/sizeof(WCHAR) );
    add->szFeatures[0] = 0;

    return MMSYSERR_NOERROR;
}