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
struct TYPE_5__ {int obj_class; } ;
struct TYPE_7__ {int /*<<< orphan*/  error; scalar_t__ attr; TYPE_1__ header; } ;
struct TYPE_6__ {int gmode; } ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__* HPDF_PageAttr ;
typedef  TYPE_3__* HPDF_Page ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_INVALID_OBJECT ; 
 int /*<<< orphan*/  HPDF_INVALID_PAGE ; 
 int HPDF_OCLASS_DICT ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int HPDF_OSUBCLASS_PAGE ; 
 int /*<<< orphan*/  HPDF_PAGE_INVALID_GMODE ; 
 int /*<<< orphan*/  HPDF_RaiseError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Page_CheckState  (HPDF_Page  page,
                       HPDF_UINT  mode)
{
    if (!page)
        return HPDF_INVALID_OBJECT;

    if (page->header.obj_class != (HPDF_OSUBCLASS_PAGE | HPDF_OCLASS_DICT))
        return HPDF_INVALID_PAGE;

    if (!(((HPDF_PageAttr)page->attr)->gmode & mode))
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_GMODE, 0);

    return HPDF_OK;
}