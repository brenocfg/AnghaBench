#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t ncb_lsn; int /*<<< orphan*/  ncb_lana_num; } ;
struct TYPE_9__ {size_t sessionsLen; TYPE_1__* sessions; } ;
struct TYPE_8__ {scalar_t__ inUse; } ;
typedef  TYPE_2__ NetBIOSAdapter ;
typedef  TYPE_3__ NCB ;

/* Variables and functions */
 TYPE_2__* nbGetAdapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbHangup (TYPE_2__*,TYPE_3__ const*) ; 

void NetBIOSHangupSession(const NCB *ncb)
{
    NetBIOSAdapter *adapter;

    if (!ncb) return;

    adapter = nbGetAdapter(ncb->ncb_lana_num);
    if (adapter)
    {
        if (ncb->ncb_lsn < adapter->sessionsLen &&
         adapter->sessions[ncb->ncb_lsn].inUse)
            nbHangup(adapter, ncb);
    }
}