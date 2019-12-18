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
typedef  int /*<<< orphan*/  HPDF_Point3D ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  int /*<<< orphan*/ * HPDF_3DMeasure ;

/* Variables and functions */
 scalar_t__ HPDF_Dict_AddName (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ HPDF_Dict_AddPoint3D (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HPDF_3DMeasure
HPDF_3DC3DMeasure_New(HPDF_MMgr mmgr,
					  HPDF_Xref xref,
					  HPDF_Point3D    firstanchorpoint,
					  HPDF_Point3D    textanchorpoint
					  )
{
	HPDF_3DMeasure measure;
	HPDF_STATUS ret = HPDF_OK;


	HPDF_PTRACE((" HPDF_3DC3DMeasure_New\n"));

	measure = HPDF_Dict_New (mmgr);
	if (!measure)
		return NULL;

	if (HPDF_Xref_Add (xref, measure) != HPDF_OK)
		return NULL;

	ret += HPDF_Dict_AddPoint3D(measure, "A1", firstanchorpoint);
	ret += HPDF_Dict_AddPoint3D(measure, "TP", textanchorpoint);

	ret += HPDF_Dict_AddName (measure, "Type", "3DMeasure");
	ret += HPDF_Dict_AddName (measure, "Subtype", "3DC");

	if (ret != HPDF_OK)
		return NULL;

	return measure;
}