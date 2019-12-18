#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int obj_class; } ;
typedef  scalar_t__ HPDF_Pages ;
typedef  TYPE_1__ HPDF_Obj_Header ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FALSE ; 
 int HPDF_OCLASS_DICT ; 
 int HPDF_OSUBCLASS_PAGES ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_BOOL
HPDF_Pages_Validate  (HPDF_Pages  pages)
{
    HPDF_Obj_Header *header = (HPDF_Obj_Header *)pages;

    HPDF_PTRACE((" HPDF_Pages_Validate\n"));

    if (!pages || header->obj_class != (HPDF_OCLASS_DICT |
                HPDF_OSUBCLASS_PAGES))
        return HPDF_FALSE;

    return HPDF_TRUE;
}