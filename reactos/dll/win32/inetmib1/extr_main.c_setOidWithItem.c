#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int idLength; int /*<<< orphan*/ * ids; } ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ AsnObjectIdentifier ;

/* Variables and functions */
 scalar_t__ SnmpUtilOidAppend (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ SnmpUtilOidCpy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SnmpUtilOidFree (TYPE_1__*) ; 

__attribute__((used)) static INT setOidWithItem(AsnObjectIdentifier *dst, AsnObjectIdentifier *base,
    UINT item)
{
    UINT id;
    AsnObjectIdentifier oid;
    INT ret;

    SnmpUtilOidFree(dst);
    ret = SnmpUtilOidCpy(dst, base);
    if (ret)
    {
        oid.idLength = 1;
        oid.ids = &id;
        id = item;
        ret = SnmpUtilOidAppend(dst, &oid);
    }
    return ret;
}