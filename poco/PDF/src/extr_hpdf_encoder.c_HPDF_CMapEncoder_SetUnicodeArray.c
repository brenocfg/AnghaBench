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
struct TYPE_8__ {int** unicode_map; } ;
struct TYPE_7__ {int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {int unicode; int code; } ;
typedef  TYPE_1__ HPDF_UnicodeMap_Rec ;
typedef  TYPE_2__* HPDF_Encoder ;
typedef  TYPE_3__* HPDF_CMapEncoderAttr ;
typedef  size_t HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_CMapEncoder_SetUnicodeArray  (HPDF_Encoder                 encoder,
                                   const HPDF_UnicodeMap_Rec   *array)
{
    HPDF_CMapEncoderAttr attr = (HPDF_CMapEncoderAttr)encoder->attr;

    HPDF_PTRACE ((" HPDF_CMapEncoder_SetUnicodeArray\n"));

    if (array != NULL)
        while (array->unicode != 0xffff) {
            HPDF_BYTE l = (HPDF_BYTE)array->code;
            HPDF_BYTE h = (HPDF_BYTE)(array->code >> 8);
            attr->unicode_map[l][h] = array->unicode;
            array++;
        }
}