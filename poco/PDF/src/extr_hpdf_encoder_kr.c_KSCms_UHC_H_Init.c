#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int suppliment; int uid_offset; int* xuid; scalar_t__ ordering; scalar_t__ registry; int /*<<< orphan*/  is_trial_byte_fn; int /*<<< orphan*/  is_lead_byte_fn; } ;
struct TYPE_11__ {int /*<<< orphan*/  type; TYPE_1__* error; scalar_t__ attr; } ;
struct TYPE_10__ {scalar_t__ error_no; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_Encoder ;
typedef  TYPE_3__* HPDF_CMapEncoderAttr ;

/* Variables and functions */
 int /*<<< orphan*/  CMAP_ARRAY_KSCms_UHC_H ; 
 int /*<<< orphan*/  CP949_UNICODE_ARRAY ; 
 scalar_t__ HPDF_CMapEncoder_AddCMap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_CMapEncoder_AddNotDefRange (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_CMapEncoder_InitAttr (TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_CMapEncoder_SetUnicodeArray (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_ENCODER_TYPE_DOUBLE_BYTE ; 
 scalar_t__ HPDF_LIMIT_MAX_NAME_LEN ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_StrCpy (scalar_t__,char*,scalar_t__) ; 
 scalar_t__ KSCms_UHC_AddCodeSpaceRange (TYPE_2__*) ; 
 int /*<<< orphan*/  KSCms_UHC_IsLeadByte ; 
 int /*<<< orphan*/  KSCms_UHC_IsTrialByte ; 
 int /*<<< orphan*/  KSCms_UHC_NOTDEF_RANGE ; 

__attribute__((used)) static HPDF_STATUS
KSCms_UHC_H_Init  (HPDF_Encoder  encoder)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    if ((ret = HPDF_CMapEncoder_InitAttr (encoder)) != HPDF_OK)
        return ret;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    if (HPDF_CMapEncoder_AddCMap (encoder, CMAP_ARRAY_KSCms_UHC_H) != HPDF_OK)
        return encoder->error->error_no;

    if ((ret = KSCms_UHC_AddCodeSpaceRange (encoder)) != HPDF_OK)
        return ret;

    if (HPDF_CMapEncoder_AddNotDefRange (encoder, KSCms_UHC_NOTDEF_RANGE)
                != HPDF_OK)
        return encoder->error->error_no;

    HPDF_CMapEncoder_SetUnicodeArray (encoder, CP949_UNICODE_ARRAY);

    attr->is_lead_byte_fn = KSCms_UHC_IsLeadByte;
    attr->is_trial_byte_fn = KSCms_UHC_IsTrialByte;
    HPDF_StrCpy (attr->registry, "Adobe", attr->registry +
                HPDF_LIMIT_MAX_NAME_LEN);
    HPDF_StrCpy (attr->ordering, "Korea1", attr->ordering +
                HPDF_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 1;
    attr->uid_offset = 430;
    attr->xuid[0] = 1;
    attr->xuid[1] = 10;
    attr->xuid[2] = 25409;

    encoder->type = HPDF_ENCODER_TYPE_DOUBLE_BYTE;

    return HPDF_OK;
}