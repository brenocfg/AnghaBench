#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ ** unicode_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;
typedef  int /*<<< orphan*/  HPDF_UNICODE ;
typedef  int HPDF_UINT16 ;
typedef  TYPE_1__* HPDF_Encoder ;
typedef  TYPE_2__* HPDF_CMapEncoderAttr ;
typedef  size_t HPDF_BYTE ;

/* Variables and functions */

HPDF_UNICODE
HPDF_CMapEncoder_ToUnicode  (HPDF_Encoder  encoder,
                             HPDF_UINT16   code)
{
    HPDF_BYTE l = (HPDF_BYTE)code;
    HPDF_BYTE h = (HPDF_BYTE)(code >> 8);
    HPDF_CMapEncoderAttr attr = (HPDF_CMapEncoderAttr)encoder->attr;

    return attr->unicode_map[l][h];
}