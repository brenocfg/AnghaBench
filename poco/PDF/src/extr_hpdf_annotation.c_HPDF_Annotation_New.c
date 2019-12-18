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
struct TYPE_10__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_12__ {TYPE_1__ header; } ;
struct TYPE_11__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__ HPDF_Rect ;
typedef  scalar_t__ HPDF_REAL ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  size_t HPDF_INT ;
typedef  int /*<<< orphan*/  HPDF_Array ;
typedef  TYPE_3__* HPDF_Annotation ;
typedef  scalar_t__ HPDF_AnnotType ;

/* Variables and functions */
 char** HPDF_ANNOT_TYPE_NAMES ; 
 scalar_t__ HPDF_Array_AddReal (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_Array_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_AddName (TYPE_3__*,char*,char*) ; 
 TYPE_3__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_ANNOTATION ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_3__*) ; 

HPDF_Annotation
HPDF_Annotation_New  (HPDF_MMgr       mmgr,
                      HPDF_Xref       xref,
                      HPDF_AnnotType  type,
                      HPDF_Rect       rect)
{
    HPDF_Annotation annot;
    HPDF_Array array;
    HPDF_STATUS ret = HPDF_OK;
    HPDF_REAL tmp;

    HPDF_PTRACE((" HPDF_Annotation_New\n"));

    annot = HPDF_Dict_New (mmgr);
    if (!annot)
        return NULL;

    if (HPDF_Xref_Add (xref, annot) != HPDF_OK)
        return NULL;

    array = HPDF_Array_New (mmgr);
    if (!array)
        return NULL;

    if (HPDF_Dict_Add (annot, "Rect", array) != HPDF_OK)
        return NULL;

    if (rect.top < rect.bottom) {
        tmp = rect.top;
        rect.top = rect.bottom;
        rect.bottom = tmp;
    }

    ret += HPDF_Array_AddReal (array, rect.left);
    ret += HPDF_Array_AddReal (array, rect.bottom);
    ret += HPDF_Array_AddReal (array, rect.right);
    ret += HPDF_Array_AddReal (array, rect.top);

    ret += HPDF_Dict_AddName (annot, "Type", "Annot");
    ret += HPDF_Dict_AddName (annot, "Subtype",
                    HPDF_ANNOT_TYPE_NAMES[(HPDF_INT)type]);

    if (ret != HPDF_OK)
        return NULL;

    annot->header.obj_class |= HPDF_OSUBCLASS_ANNOTATION;

    return annot;
}