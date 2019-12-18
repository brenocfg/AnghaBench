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
struct TYPE_7__ {int obj_class; } ;
struct TYPE_9__ {int /*<<< orphan*/  error; TYPE_1__ header; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_2__* HPDF_Name ;
typedef  TYPE_3__* HPDF_Image ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 TYPE_2__* HPDF_Dict_GetItem (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_INVALID_IMAGE ; 
 int HPDF_OCLASS_DICT ; 
 int /*<<< orphan*/  HPDF_OCLASS_NAME ; 
 int HPDF_OSUBCLASS_XOBJECT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_RaiseError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_StrCmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_BOOL
HPDF_Image_Validate (HPDF_Image  image)
{
    HPDF_Name subtype;

    HPDF_PTRACE ((" HPDF_Image_Validate\n"));

    if (!image)
        return HPDF_FALSE;

    if (image->header.obj_class != (HPDF_OSUBCLASS_XOBJECT |
                HPDF_OCLASS_DICT)) {
        HPDF_RaiseError (image->error, HPDF_INVALID_IMAGE, 0);
        return HPDF_FALSE;
    }

    subtype = HPDF_Dict_GetItem (image, "Subtype", HPDF_OCLASS_NAME);
    if (!subtype || HPDF_StrCmp (subtype->value, "Image") != 0) {
        HPDF_RaiseError (image->error, HPDF_INVALID_IMAGE, 0);
        return HPDF_FALSE;
    }

    return HPDF_TRUE;
}