#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  error; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Outline ;

/* Variables and functions */
 scalar_t__ HPDF_Dict_Add (TYPE_1__*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_Dict_GetItem (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OCLASS_DICT ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_STATUS
AddChild  (HPDF_Outline  parent,
           HPDF_Outline  item)
{
    HPDF_Outline first = (HPDF_Outline)HPDF_Dict_GetItem (parent, "First",
                    HPDF_OCLASS_DICT);
    HPDF_Outline last = (HPDF_Outline)HPDF_Dict_GetItem (parent, "Last",
                    HPDF_OCLASS_DICT);
    HPDF_STATUS ret = 0;

    HPDF_PTRACE((" AddChild\n"));

    if (!first)
        ret += HPDF_Dict_Add (parent, "First", item);

    if (last) {
        ret += HPDF_Dict_Add (last, "Next", item);
        ret += HPDF_Dict_Add (item, "Prev", last);
    }

    ret += HPDF_Dict_Add (parent, "Last", item);
    ret += HPDF_Dict_Add (item, "Parent", parent);

    if (ret != HPDF_OK)
        return HPDF_Error_GetCode (item->error);

    return HPDF_OK;
}