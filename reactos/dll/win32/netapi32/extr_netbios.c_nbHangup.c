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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {size_t ncb_lsn; } ;
struct TYPE_9__ {size_t sessionsLen; TYPE_1__* sessions; } ;
struct TYPE_8__ {scalar_t__ state; int /*<<< orphan*/  inUse; } ;
typedef  TYPE_1__ NetBIOSSession ;
typedef  TYPE_2__ NetBIOSAdapter ;
typedef  TYPE_3__ NCB ;

/* Variables and functions */
 scalar_t__ HANGUP_PENDING ; 
 int /*<<< orphan*/  NRC_BRIDGE ; 
 int /*<<< orphan*/  NRC_INVADDRESS ; 
 int /*<<< orphan*/  NRC_SNUMOUT ; 
 scalar_t__ SESSION_ESTABLISHED ; 
 int /*<<< orphan*/  nbInternalHangup (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static UCHAR nbHangup(NetBIOSAdapter *adapter, const NCB *ncb)
{
    UCHAR ret;
    NetBIOSSession *session;

    if (!adapter) return NRC_BRIDGE;
    if (!ncb) return NRC_INVADDRESS;
    if (ncb->ncb_lsn >= adapter->sessionsLen) return NRC_SNUMOUT;
    if (!adapter->sessions[ncb->ncb_lsn].inUse) return NRC_SNUMOUT;

    session = &adapter->sessions[ncb->ncb_lsn];
    if (session->state != SESSION_ESTABLISHED)
        ret = NRC_SNUMOUT;
    else
    {
        session->state = HANGUP_PENDING;
        ret = nbInternalHangup(adapter, session);
    }
    return ret;
}