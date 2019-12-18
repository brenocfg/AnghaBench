#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct GenericTable {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {TYPE_3__* table; } ;
struct TYPE_7__ {int /*<<< orphan*/  dwAddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SnmpVarBind ;
typedef  int /*<<< orphan*/  MIB_IPADDRROW ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  AsnObjectIdentifier ;
typedef  int /*<<< orphan*/  AsnInteger32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_OID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFINE_SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOSUCHNAME ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_READONLY ; 
#define  SNMP_PDU_GET 130 
#define  SNMP_PDU_GETNEXT 129 
#define  SNMP_PDU_SET 128 
 int /*<<< orphan*/  SnmpUtilOidToA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compareIpAddrRow ; 
 int /*<<< orphan*/  getItemAndInstanceFromTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,struct GenericTable*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* ipAddrTable ; 
 int /*<<< orphan*/  mapStructEntryToValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mib2IpAddr ; 
 int /*<<< orphan*/  mib2IpAddrMap ; 
 int /*<<< orphan*/  oidToIpAddrRow ; 
 int /*<<< orphan*/  setOidWithItemAndIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL mib2IpAddrQuery(BYTE bPduType, SnmpVarBind *pVarBind,
    AsnInteger32 *pErrorStatus)
{
    AsnObjectIdentifier myOid = DEFINE_OID(mib2IpAddr);
    UINT tableIndex = 0, item = 0;
    BOOL ret = TRUE;

    TRACE("(0x%02x, %s, %p)\n", bPduType, SnmpUtilOidToA(&pVarBind->name),
        pErrorStatus);

    switch (bPduType)
    {
    case SNMP_PDU_GET:
    case SNMP_PDU_GETNEXT:
        *pErrorStatus = getItemAndInstanceFromTable(&pVarBind->name,
            &myOid, 4, bPduType, (struct GenericTable *)ipAddrTable,
            sizeof(MIB_IPADDRROW), oidToIpAddrRow, compareIpAddrRow, &item,
            &tableIndex);
        if (!*pErrorStatus)
        {
            assert(tableIndex);
            assert(item);
            *pErrorStatus = mapStructEntryToValue(mib2IpAddrMap,
                DEFINE_SIZEOF(mib2IpAddrMap),
                &ipAddrTable->table[tableIndex - 1], item, pVarBind);
            if (!*pErrorStatus && bPduType == SNMP_PDU_GETNEXT)
                ret = setOidWithItemAndIpAddr(&pVarBind->name, &myOid, item,
                    ipAddrTable->table[tableIndex - 1].dwAddr);
        }
        break;
    case SNMP_PDU_SET:
        *pErrorStatus = SNMP_ERRORSTATUS_READONLY;
        ret = FALSE;
        break;
    default:
        FIXME("0x%02x: unsupported PDU type\n", bPduType);
        *pErrorStatus = SNMP_ERRORSTATUS_NOSUCHNAME;
    }
    return ret;
}