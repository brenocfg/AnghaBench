#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {scalar_t__ gmode; TYPE_1__* gstate; } ;
struct TYPE_5__ {scalar_t__ prev; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__* HPDF_PageAttr ;
typedef  int /*<<< orphan*/  HPDF_Page ;
typedef  TYPE_3__* HPDF_Dict ;

/* Variables and functions */
 scalar_t__ HPDF_GMODE_PATH_OBJECT ; 
 scalar_t__ HPDF_GMODE_TEXT_OBJECT ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_Page_EndPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Page_EndText (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Page_GRestore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HPDF_STATUS
Page_BeforeWrite  (HPDF_Dict    obj)
{
    HPDF_STATUS ret;
    HPDF_Page page = (HPDF_Page)obj;
    HPDF_PageAttr attr = (HPDF_PageAttr)obj->attr;

    HPDF_PTRACE((" HPDF_Page_BeforeWrite\n"));

    if (attr->gmode == HPDF_GMODE_PATH_OBJECT) {
        HPDF_PTRACE((" HPDF_Page_BeforeWrite warning path object is not"
                    " end\n"));

        if ((ret = HPDF_Page_EndPath (page)) != HPDF_OK)
           return ret;
    }

    if (attr->gmode == HPDF_GMODE_TEXT_OBJECT) {
        HPDF_PTRACE((" HPDF_Page_BeforeWrite warning text block is not end\n"));

        if ((ret = HPDF_Page_EndText (page)) != HPDF_OK)
            return ret;
    }

    if (attr->gstate)
        while (attr->gstate->prev) {
            if ((ret = HPDF_Page_GRestore (page)) != HPDF_OK)
                return ret;
        }

    return HPDF_OK;
}