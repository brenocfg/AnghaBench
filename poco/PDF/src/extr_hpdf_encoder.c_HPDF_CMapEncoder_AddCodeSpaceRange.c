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
struct TYPE_5__ {int /*<<< orphan*/  code_space_range; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Encoder ;
typedef  int /*<<< orphan*/  HPDF_CidRange_Rec ;
typedef  TYPE_2__* HPDF_CMapEncoderAttr ;

/* Variables and functions */
 int /*<<< orphan*/  AddCidRainge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_CMapEncoder_AddCodeSpaceRange  (HPDF_Encoder        encoder,
                                     HPDF_CidRange_Rec   range)
{
    HPDF_CMapEncoderAttr attr = (HPDF_CMapEncoderAttr)encoder->attr;

    HPDF_PTRACE ((" HPDF_CMapEncoder_AddNotDefRange\n"));

    return AddCidRainge (encoder->mmgr, range, attr->code_space_range);
}