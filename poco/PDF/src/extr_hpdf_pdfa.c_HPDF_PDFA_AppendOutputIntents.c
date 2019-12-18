#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  error; int /*<<< orphan*/ * catalog; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  xref; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Doc ;
typedef  int /*<<< orphan*/ * HPDF_Dict ;
typedef  int /*<<< orphan*/ * HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HPDF_Array_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_CheckError (int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_Dict_Add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_Dict_AddName (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  HPDF_Dict_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HPDF_Dict_GetItem (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Error_GetDetailCode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_HasDoc (TYPE_1__*) ; 
 scalar_t__ HPDF_INVALID_DOCUMENT ; 
 int /*<<< orphan*/  HPDF_OCLASS_ARRAY ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/ * HPDF_String_New (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HPDF_STATUS
HPDF_PDFA_AppendOutputIntents(HPDF_Doc pdf, const char *iccname, HPDF_Dict iccdict)
{
    HPDF_Array intents;
    HPDF_Dict intent;
    HPDF_STATUS ret;
    if (!HPDF_HasDoc (pdf))
        return HPDF_INVALID_DOCUMENT;

    /* prepare intent */
    intent = HPDF_Dict_New (pdf->mmgr);
    ret = HPDF_Xref_Add (pdf->xref, intent);
    if ( ret != HPDF_OK) {
        HPDF_Dict_Free(intent);
        return ret;
    }
    ret += HPDF_Dict_AddName (intent, "Type", "OutputIntent");
    ret += HPDF_Dict_AddName (intent, "S", "GTS_PDFA1");
    ret += HPDF_Dict_Add (intent, "OutputConditionIdentifier", HPDF_String_New (pdf->mmgr, iccname, NULL));
    ret += HPDF_Dict_Add (intent, "OutputCondition", HPDF_String_New (pdf->mmgr, iccname,NULL));
    ret += HPDF_Dict_Add (intent, "Info", HPDF_String_New (pdf->mmgr, iccname, NULL));
    ret += HPDF_Dict_Add (intent, "DestOutputProfile ", iccdict);
    if ( ret != HPDF_OK) {
        HPDF_Dict_Free(intent);
        return ret;
    }

    /* Copied from HPDF_AddIntent - not public function */
    intents = HPDF_Dict_GetItem (pdf->catalog, "OutputIntents", HPDF_OCLASS_ARRAY);
    if (intents == NULL) {
        intents = HPDF_Array_New (pdf->mmgr);
        if (intents) {
            HPDF_STATUS ret = HPDF_Dict_Add (pdf->catalog, "OutputIntents", intents);
            if (ret != HPDF_OK) {
                HPDF_CheckError (&pdf->error);
                return HPDF_Error_GetDetailCode (&pdf->error);
            }
        }
    }

    HPDF_Array_Add(intents,intent);
    return HPDF_Error_GetDetailCode (&pdf->error);
}