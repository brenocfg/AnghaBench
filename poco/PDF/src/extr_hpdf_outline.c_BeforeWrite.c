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
struct TYPE_2__ {int value; } ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_Outline ;
typedef  TYPE_1__* HPDF_Number ;
typedef  scalar_t__ HPDF_Dict ;

/* Variables and functions */
 int CountChild (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Dict_AddNumber (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  HPDF_Dict_GetItem (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Dict_RemoveElement (scalar_t__,char*) ; 
 int /*<<< orphan*/  HPDF_OCLASS_NUMBER ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_Outline_GetOpened (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_STATUS
BeforeWrite  (HPDF_Dict obj)
{
    HPDF_Number n = (HPDF_Number)HPDF_Dict_GetItem (obj, "Count",
                HPDF_OCLASS_NUMBER);
    HPDF_UINT count = CountChild ((HPDF_Outline)obj);

    HPDF_PTRACE((" BeforeWrite\n"));

    if (count == 0 && n)
        return HPDF_Dict_RemoveElement (obj, "Count");

    if (!HPDF_Outline_GetOpened ((HPDF_Outline)obj))
        count = count * -1;

    if (n)
        n->value = count;
    else
        if (count)
            return HPDF_Dict_AddNumber (obj, "Count", count);

    return HPDF_OK;
}