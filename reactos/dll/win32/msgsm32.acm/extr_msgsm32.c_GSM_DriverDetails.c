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
struct TYPE_3__ {int vdwACM; int vdwDriver; int cFormatTags; scalar_t__* szFeatures; int /*<<< orphan*/  szLicensing; int /*<<< orphan*/  szCopyright; int /*<<< orphan*/  szLongName; int /*<<< orphan*/  szShortName; int /*<<< orphan*/ * hicon; scalar_t__ cFilterTags; int /*<<< orphan*/  fdwSupport; int /*<<< orphan*/  wPid; int /*<<< orphan*/  wMid; int /*<<< orphan*/  fccComp; int /*<<< orphan*/  fccType; } ;
typedef  TYPE_1__* PACMDRIVERDETAILSW ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_FCCCOMP_UNDEFINED ; 
 int /*<<< orphan*/  ACMDRIVERDETAILS_FCCTYPE_AUDIOCODEC ; 
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CODEC ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MM_MICROSOFT ; 
 int /*<<< orphan*/  MM_MSFT_ACM_GSM610 ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	LRESULT GSM_DriverDetails(PACMDRIVERDETAILSW add)
{
    add->fccType = ACMDRIVERDETAILS_FCCTYPE_AUDIOCODEC;
    add->fccComp = ACMDRIVERDETAILS_FCCCOMP_UNDEFINED;
    /* Details found from probing native msgsm32.acm */
    add->wMid = MM_MICROSOFT;
    add->wPid = MM_MSFT_ACM_GSM610;
    add->vdwACM = 0x3320000;
    add->vdwDriver = 0x4000000;
    add->fdwSupport = ACMDRIVERDETAILS_SUPPORTF_CODEC;
    add->cFormatTags = 2;
    add->cFilterTags = 0;
    add->hicon = NULL;
    MultiByteToWideChar( CP_ACP, 0, "Microsoft GSM 6.10", -1,
                         add->szShortName, ARRAY_SIZE( add->szShortName ));
    MultiByteToWideChar( CP_ACP, 0, "Wine GSM 6.10 libgsm codec", -1,
                         add->szLongName, ARRAY_SIZE( add->szLongName ));
    MultiByteToWideChar( CP_ACP, 0, "Brought to you by the Wine team...", -1,
                         add->szCopyright, ARRAY_SIZE( add->szCopyright ));
    MultiByteToWideChar( CP_ACP, 0, "Refer to LICENSE file", -1,
                         add->szLicensing, ARRAY_SIZE( add->szLicensing ));
    add->szFeatures[0] = 0;
    return MMSYSERR_NOERROR;
}