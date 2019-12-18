#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  writing_mode; scalar_t__ suppliment; scalar_t__ ordering; scalar_t__ registry; int /*<<< orphan*/ * is_trial_byte_fn; int /*<<< orphan*/ * is_lead_byte_fn; } ;
struct TYPE_10__ {int /*<<< orphan*/  type; TYPE_1__* error; scalar_t__ attr; int /*<<< orphan*/  encode_text_fn; int /*<<< orphan*/  to_unicode_fn; int /*<<< orphan*/  byte_type_fn; } ;
struct TYPE_9__ {scalar_t__ error_no; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_Encoder ;
typedef  TYPE_3__* HPDF_CMapEncoderAttr ;

/* Variables and functions */
 scalar_t__ HPDF_CMapEncoder_AddCMap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_CMapEncoder_AddCodeSpaceRange (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_CMapEncoder_AddNotDefRange (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_CMapEncoder_InitAttr (TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_ENCODER_TYPE_DOUBLE_BYTE ; 
 scalar_t__ HPDF_LIMIT_MAX_NAME_LEN ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_StrCpy (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_WMODE_HORIZONTAL ; 
 int /*<<< orphan*/  UTF8_CID_RANGE ; 
 int /*<<< orphan*/  UTF8_Encoder_ByteType_Func ; 
 int /*<<< orphan*/  UTF8_Encoder_EncodeText_Func ; 
 int /*<<< orphan*/  UTF8_Encoder_ToUnicode_Func ; 
 int /*<<< orphan*/  UTF8_NOTDEF_RANGE ; 
 int /*<<< orphan*/  UTF8_SPACE_RANGE ; 

__attribute__((used)) static HPDF_STATUS
UTF8_Init  (HPDF_Encoder  encoder)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    if ((ret = HPDF_CMapEncoder_InitAttr (encoder)) != HPDF_OK)
        return ret;

    /*
     * We override these two
     */
    encoder->byte_type_fn = UTF8_Encoder_ByteType_Func;
    encoder->to_unicode_fn = UTF8_Encoder_ToUnicode_Func;
    encoder->encode_text_fn = UTF8_Encoder_EncodeText_Func;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    if (HPDF_CMapEncoder_AddCMap (encoder, UTF8_CID_RANGE) != HPDF_OK)
        return encoder->error->error_no;

    if (HPDF_CMapEncoder_AddCodeSpaceRange (encoder, UTF8_SPACE_RANGE)
	       != HPDF_OK)
      return encoder->error->error_no;

    if (HPDF_CMapEncoder_AddNotDefRange (encoder, UTF8_NOTDEF_RANGE)
                != HPDF_OK)
        return encoder->error->error_no;

    attr->is_lead_byte_fn = NULL;
    attr->is_trial_byte_fn = NULL;

    HPDF_StrCpy (attr->registry, "Adobe", attr->registry +
                HPDF_LIMIT_MAX_NAME_LEN);
    HPDF_StrCpy (attr->ordering, "Identity-H", attr->ordering +
                HPDF_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 0;
    attr->writing_mode = HPDF_WMODE_HORIZONTAL;
    
    /* Not sure about this
    attr->uid_offset = 0;
    attr->xuid[0] = 0;
    attr->xuid[1] = 0;
    attr->xuid[2] = 0;
    */

    encoder->type = HPDF_ENCODER_TYPE_DOUBLE_BYTE;

    return HPDF_OK;
}