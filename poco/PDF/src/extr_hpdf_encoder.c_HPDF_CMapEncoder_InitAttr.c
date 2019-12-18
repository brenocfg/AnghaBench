#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int** unicode_map; void* code_space_range; void* notdef_range; void* cmap_range; int /*<<< orphan*/  writing_mode; } ;
struct TYPE_8__ {TYPE_1__* error; int /*<<< orphan*/  mmgr; TYPE_3__* attr; } ;
struct TYPE_7__ {int /*<<< orphan*/  error_no; } ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__* HPDF_Encoder ;
typedef  int /*<<< orphan*/  HPDF_CMapEncoderAttr_Rec ;
typedef  TYPE_3__* HPDF_CMapEncoderAttr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_DEF_ITEMS_PER_BLOCK ; 
 int /*<<< orphan*/  HPDF_DEF_RANGE_TBL_NUM ; 
 TYPE_3__* HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_INVALID_ENCODER ; 
 void* HPDF_List_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_WMODE_HORIZONTAL ; 

HPDF_STATUS
HPDF_CMapEncoder_InitAttr  (HPDF_Encoder  encoder)
{
    HPDF_CMapEncoderAttr encoder_attr;
    HPDF_UINT i;
    HPDF_UINT j;

    HPDF_PTRACE ((" HPDF_CMapEncoder_InitAttr\n"));

    if (encoder->attr)
        return HPDF_INVALID_ENCODER;

    encoder_attr = HPDF_GetMem(encoder->mmgr,
            sizeof(HPDF_CMapEncoderAttr_Rec));

    if (!encoder_attr)
        return encoder->error->error_no;

    HPDF_MemSet (encoder_attr, 0, sizeof(HPDF_CMapEncoderAttr_Rec));
    encoder->attr = encoder_attr;

    encoder_attr->writing_mode = HPDF_WMODE_HORIZONTAL;

    for (i = 0; i <= 255; i++) {
        for (j = 0; j <= 255; j++) {
            /* undefined charactors are replaced to square */
            encoder_attr->unicode_map[i][j] = 0x25A1;
        }
    }

    /* create cmap range */
    encoder_attr->cmap_range = HPDF_List_New (encoder->mmgr,
                HPDF_DEF_RANGE_TBL_NUM);
    if (!encoder_attr->cmap_range)
        return encoder->error->error_no;

    encoder_attr->notdef_range = HPDF_List_New (encoder->mmgr,
                HPDF_DEF_ITEMS_PER_BLOCK);
    if (!encoder_attr->notdef_range)
        return encoder->error->error_no;

    encoder_attr->code_space_range = HPDF_List_New (encoder->mmgr,
                HPDF_DEF_ITEMS_PER_BLOCK);
    if (!encoder_attr->code_space_range)
        return encoder->error->error_no;

    return HPDF_OK;
}