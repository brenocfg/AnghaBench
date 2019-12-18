#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int /*<<< orphan*/  cs; TYPE_2__ impl; TYPE_1__* transport; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* hangup ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ NetBIOSSession ;
typedef  TYPE_4__ NetBIOSAdapter ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NRC_BRIDGE ; 
 int /*<<< orphan*/  NRC_ILLCMD ; 
 int /*<<< orphan*/  NRC_SNUMOUT ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UCHAR nbInternalHangup(NetBIOSAdapter *adapter, NetBIOSSession *session)
{
    UCHAR ret;

    if (!adapter) return NRC_BRIDGE;
    if (!session) return NRC_SNUMOUT;

    if (adapter->transport->hangup)
        ret = adapter->transport->hangup(adapter->impl.data, session->data);
    else
        ret = NRC_ILLCMD;
    EnterCriticalSection(&adapter->cs);
    memset(session, 0, sizeof(NetBIOSSession));
    LeaveCriticalSection(&adapter->cs);
    return ret;
}