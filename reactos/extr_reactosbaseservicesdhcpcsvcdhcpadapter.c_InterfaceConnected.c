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
struct TYPE_3__ {scalar_t__ dwOperStatus; int /*<<< orphan*/  dwIndex; } ;
typedef  TYPE_1__ MIB_IFROW ;

/* Variables and functions */
 int /*<<< orphan*/  DH_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ IF_OPER_STATUS_CONNECTED ; 
 scalar_t__ IF_OPER_STATUS_OPERATIONAL ; 
 int /*<<< orphan*/  MID_TRACE ; 

int
InterfaceConnected(const MIB_IFROW* IfEntry)
{
    if (IfEntry->dwOperStatus == IF_OPER_STATUS_CONNECTED ||
        IfEntry->dwOperStatus == IF_OPER_STATUS_OPERATIONAL)
        return 1;

    DH_DbgPrint(MID_TRACE,("Interface %d is down\n", IfEntry->dwIndex));
    return 0;
}