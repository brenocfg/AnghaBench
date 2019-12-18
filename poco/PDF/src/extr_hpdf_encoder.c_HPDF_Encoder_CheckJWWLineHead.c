#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ const* jww_line_head; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ attr; } ;
typedef  scalar_t__ HPDF_UINT16 ;
typedef  size_t HPDF_UINT ;
typedef  TYPE_1__* HPDF_Encoder ;
typedef  TYPE_2__* HPDF_CMapEncoderAttr ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 scalar_t__ HPDF_ENCODER_TYPE_DOUBLE_BYTE ; 
 int /*<<< orphan*/  HPDF_Encoder_Validate (TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_FALSE ; 
 size_t HPDF_MAX_JWW_NUM ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_BOOL
HPDF_Encoder_CheckJWWLineHead  (HPDF_Encoder        encoder,
                                const HPDF_UINT16   code)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_UINT j;

    HPDF_PTRACE ((" HPDF_Encoder_CheckJWWLineHead\n"));

    if (!HPDF_Encoder_Validate (encoder))
        return HPDF_FALSE;

    if (encoder->type != HPDF_ENCODER_TYPE_DOUBLE_BYTE)
        return HPDF_FALSE;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    for (j = 0; j < HPDF_MAX_JWW_NUM; j++) {
        if (code == attr->jww_line_head[j])
            return HPDF_TRUE;

        if (attr->jww_line_head[j] == 0)
            return HPDF_FALSE;
    }

    return HPDF_FALSE;
}