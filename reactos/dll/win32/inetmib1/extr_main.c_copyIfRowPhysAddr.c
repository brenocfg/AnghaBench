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
struct TYPE_2__ {int /*<<< orphan*/  bPhysAddr; scalar_t__ dwPhysAddrLen; } ;
typedef  TYPE_1__* PMIB_IFROW ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  AsnAny ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_OCTETSTRING ; 
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIB_IFROW ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOERROR ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOSUCHNAME ; 
 int /*<<< orphan*/  dwPhysAddrLen ; 
 int /*<<< orphan*/  setStringValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD copyIfRowPhysAddr(AsnAny *value, void *src)
{
    PMIB_IFROW row = (PMIB_IFROW)((BYTE *)src -
                                  FIELD_OFFSET(MIB_IFROW, dwPhysAddrLen));
    DWORD ret;

    if (row->dwPhysAddrLen)
    {
        setStringValue(value, ASN_OCTETSTRING, row->dwPhysAddrLen,
                       row->bPhysAddr);
        ret = SNMP_ERRORSTATUS_NOERROR;
    }
    else
        ret = SNMP_ERRORSTATUS_NOSUCHNAME;
    return ret;
}