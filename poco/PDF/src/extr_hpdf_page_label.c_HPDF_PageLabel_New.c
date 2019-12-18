#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  def_encoder; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int HPDF_PageNumStyle ;
typedef  int /*<<< orphan*/  HPDF_INT ;
typedef  TYPE_1__* HPDF_Doc ;
typedef  int /*<<< orphan*/ * HPDF_Dict ;

/* Variables and functions */
 scalar_t__ HPDF_Dict_Add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_AddName (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ HPDF_Dict_AddNumber (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Dict_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
#define  HPDF_PAGE_NUM_STYLE_DECIMAL 132 
#define  HPDF_PAGE_NUM_STYLE_LOWER_LETTERS 131 
#define  HPDF_PAGE_NUM_STYLE_LOWER_ROMAN 130 
 int /*<<< orphan*/  HPDF_PAGE_NUM_STYLE_OUT_OF_RANGE ; 
#define  HPDF_PAGE_NUM_STYLE_UPPER_LETTERS 129 
#define  HPDF_PAGE_NUM_STYLE_UPPER_ROMAN 128 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_String_New (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

HPDF_Dict
HPDF_PageLabel_New  (HPDF_Doc             pdf,
                     HPDF_PageNumStyle    style,
                     HPDF_INT             first_page,
                     const char     *prefix)
{
    HPDF_Dict obj = HPDF_Dict_New (pdf->mmgr);

    HPDF_PTRACE ((" HPDF_PageLabel_New\n"));

    if (!obj)
        return NULL;

    switch (style) {
        case HPDF_PAGE_NUM_STYLE_DECIMAL:
            if (HPDF_Dict_AddName (obj, "S", "D") != HPDF_OK)
                goto Fail;
            break;
        case HPDF_PAGE_NUM_STYLE_UPPER_ROMAN:
            if (HPDF_Dict_AddName (obj, "S", "R") != HPDF_OK)
                goto Fail;
            break;
        case HPDF_PAGE_NUM_STYLE_LOWER_ROMAN:
            if (HPDF_Dict_AddName (obj, "S", "r") != HPDF_OK)
                goto Fail;
            break;
        case HPDF_PAGE_NUM_STYLE_UPPER_LETTERS:
            if (HPDF_Dict_AddName (obj, "S", "A") != HPDF_OK)
                goto Fail;
            break;
        case HPDF_PAGE_NUM_STYLE_LOWER_LETTERS:
            if (HPDF_Dict_AddName (obj, "S", "a") != HPDF_OK)
                goto Fail;
            break;
        default:
            HPDF_SetError (&pdf->error, HPDF_PAGE_NUM_STYLE_OUT_OF_RANGE,
                    (HPDF_STATUS)style);
            goto Fail;
    }

    if (prefix && prefix[0] != 0)
        if (HPDF_Dict_Add (obj, "P", HPDF_String_New (pdf->mmgr, prefix,
                    pdf->def_encoder)) != HPDF_OK)
            goto Fail;

    if (first_page != 0)
        if (HPDF_Dict_AddNumber (obj, "St", first_page) != HPDF_OK)
            goto Fail;

    return obj;

Fail:
    HPDF_Dict_Free (obj);
    return NULL;
}