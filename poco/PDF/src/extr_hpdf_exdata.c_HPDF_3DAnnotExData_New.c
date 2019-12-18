#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  int /*<<< orphan*/ * HPDF_ExData ;

/* Variables and functions */
 scalar_t__ HPDF_Dict_AddName (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HPDF_ExData
HPDF_3DAnnotExData_New(HPDF_MMgr mmgr,
					   HPDF_Xref xref)
{
	HPDF_ExData exdata;
	HPDF_STATUS ret = HPDF_OK;


	HPDF_PTRACE((" HPDF_ExData_New\n"));

	exdata = HPDF_Dict_New (mmgr);
	if (!exdata)
		return NULL;

	if (HPDF_Xref_Add (xref, exdata) != HPDF_OK)
		return NULL;

	ret += HPDF_Dict_AddName (exdata, "Type", "ExData");
	ret += HPDF_Dict_AddName (exdata, "Subtype", "3DM");

	if (ret != HPDF_OK)
		return NULL;

	return exdata;
}