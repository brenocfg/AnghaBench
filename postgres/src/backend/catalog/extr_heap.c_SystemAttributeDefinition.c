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
typedef  int /*<<< orphan*/  FormData_pg_attribute ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  const** SysAtt ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ lengthof (int /*<<< orphan*/  const**) ; 

const FormData_pg_attribute *
SystemAttributeDefinition(AttrNumber attno)
{
	if (attno >= 0 || attno < -(int) lengthof(SysAtt))
		elog(ERROR, "invalid system attribute number %d", attno);
	return SysAtt[-attno - 1];
}