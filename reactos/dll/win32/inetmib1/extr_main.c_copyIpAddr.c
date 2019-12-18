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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  AsnAny ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_IPADDRESS ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOERROR ; 
 int /*<<< orphan*/  setStringValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static DWORD copyIpAddr(AsnAny *value, void *src)
{
    setStringValue(value, ASN_IPADDRESS, sizeof(DWORD), src);
    return SNMP_ERRORSTATUS_NOERROR;
}