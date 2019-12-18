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
struct structToAsnValue {int offset; int /*<<< orphan*/  (* copy ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  size_t UINT ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ SnmpVarBind ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  AsnInteger32 ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOSUCHNAME ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static AsnInteger32 mapStructEntryToValue(struct structToAsnValue *map,
    UINT mapLen, void *record, UINT id, SnmpVarBind *pVarBind)
{
    /* OIDs are 1-based */
    if (!id)
        return SNMP_ERRORSTATUS_NOSUCHNAME;
    --id;
    if (id >= mapLen)
        return SNMP_ERRORSTATUS_NOSUCHNAME;
    if (!map[id].copy)
        return SNMP_ERRORSTATUS_NOSUCHNAME;
    return map[id].copy(&pVarBind->value, (BYTE *)record + map[id].offset);
}