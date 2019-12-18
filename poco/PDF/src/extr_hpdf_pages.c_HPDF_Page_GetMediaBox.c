#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  top; int /*<<< orphan*/  right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  left; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  error; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__* HPDF_Real ;
typedef  TYPE_2__* HPDF_Page ;
typedef  TYPE_3__ HPDF_Box ;
typedef  scalar_t__ HPDF_Array ;

/* Variables and functions */
 TYPE_1__* HPDF_Array_GetItem (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_CheckError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OCLASS_ARRAY ; 
 int /*<<< orphan*/  HPDF_OCLASS_REAL ; 
 int /*<<< orphan*/  HPDF_PAGE_CANNOT_FIND_OBJECT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Page_GetInheritableItem (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Page_Validate (TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_RaiseError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_Box
HPDF_Page_GetMediaBox  (HPDF_Page   page)
{
    HPDF_Box media_box = {0, 0, 0, 0};

    HPDF_PTRACE((" HPDF_Page_GetMediaBox\n"));

    if (HPDF_Page_Validate (page)) {
        HPDF_Array array = HPDF_Page_GetInheritableItem (page, "MediaBox",
                        HPDF_OCLASS_ARRAY);

        if (array) {
            HPDF_Real r;

            r = HPDF_Array_GetItem (array, 0, HPDF_OCLASS_REAL);
            if (r)
                media_box.left = r->value;

            r = HPDF_Array_GetItem (array, 1, HPDF_OCLASS_REAL);
            if (r)
                media_box.bottom = r->value;

            r = HPDF_Array_GetItem (array, 2, HPDF_OCLASS_REAL);
            if (r)
                media_box.right = r->value;

            r = HPDF_Array_GetItem (array, 3, HPDF_OCLASS_REAL);
            if (r)
                media_box.top = r->value;

            HPDF_CheckError (page->error);
        } else HPDF_RaiseError (page->error, HPDF_PAGE_CANNOT_FIND_OBJECT, 0);
    }

    return media_box;
}