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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  HPDF_Outline ;
typedef  TYPE_1__* HPDF_Number ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Dict_GetItem (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_OCLASS_NUMBER ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_BOOL
HPDF_Outline_GetOpened  (HPDF_Outline  outline)
{
    HPDF_Number n = (HPDF_Number)HPDF_Dict_GetItem (outline, "_OPENED",
                        HPDF_OCLASS_NUMBER);

    HPDF_PTRACE((" HPDF_Outline_GetOpened\n"));

    if (!n)
        return HPDF_FALSE;

    return (HPDF_BOOL)n->value;
}