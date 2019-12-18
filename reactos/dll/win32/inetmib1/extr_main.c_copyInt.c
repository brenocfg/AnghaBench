#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  number; } ;
struct TYPE_5__ {TYPE_1__ asnValue; int /*<<< orphan*/  asnType; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ AsnAny ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_INTEGER ; 
 int /*<<< orphan*/  SNMP_ERRORSTATUS_NOERROR ; 

__attribute__((used)) static DWORD copyInt(AsnAny *value, void *src)
{
    value->asnType = ASN_INTEGER;
    value->asnValue.number = *(DWORD *)src;
    return SNMP_ERRORSTATUS_NOERROR;
}