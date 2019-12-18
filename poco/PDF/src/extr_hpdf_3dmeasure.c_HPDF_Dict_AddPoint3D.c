#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; } ;
struct TYPE_6__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_1__ HPDF_Point3D ;
typedef  TYPE_2__* HPDF_Dict ;
typedef  int /*<<< orphan*/  HPDF_Array ;

/* Variables and functions */
 scalar_t__ HPDF_Array_AddReal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Array_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 

HPDF_STATUS
HPDF_Dict_AddPoint3D(HPDF_Dict dict, const char* key, HPDF_Point3D point)
{
	HPDF_Array array;
	HPDF_STATUS ret = HPDF_OK;
	array = HPDF_Array_New (dict->mmgr);
	if (!array)
		return HPDF_Error_GetCode ( dict->error);

	if (HPDF_Dict_Add (dict, key, array) != HPDF_OK)
		return HPDF_Error_GetCode ( dict->error);

	ret += HPDF_Array_AddReal(array, point.x);
	ret += HPDF_Array_AddReal(array, point.y);
	ret += HPDF_Array_AddReal(array, point.z);

	return ret;
}