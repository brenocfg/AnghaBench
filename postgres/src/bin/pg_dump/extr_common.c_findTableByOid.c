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
typedef  int /*<<< orphan*/  TableInfo ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ findObjectByOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numTables ; 
 int /*<<< orphan*/  tblinfoindex ; 

TableInfo *
findTableByOid(Oid oid)
{
	return (TableInfo *) findObjectByOid(oid, tblinfoindex, numTables);
}