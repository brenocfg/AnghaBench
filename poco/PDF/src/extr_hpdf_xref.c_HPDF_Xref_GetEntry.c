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
struct TYPE_3__ {int /*<<< orphan*/  entries; } ;
typedef  int /*<<< orphan*/  HPDF_XrefEntry ;
typedef  TYPE_1__* HPDF_Xref ;
typedef  int /*<<< orphan*/  HPDF_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_List_ItemAt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_XrefEntry
HPDF_Xref_GetEntry  (HPDF_Xref  xref,
                     HPDF_UINT  index)
{
    HPDF_PTRACE((" HPDF_Xref_GetEntry\n"));

    return (HPDF_XrefEntry)HPDF_List_ItemAt(xref->entries, index);
}