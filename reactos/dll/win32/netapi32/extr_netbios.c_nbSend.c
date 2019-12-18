#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {size_t sessionsLen; TYPE_1__ impl; TYPE_2__* transport; TYPE_4__* sessions; } ;
struct TYPE_12__ {scalar_t__ state; int /*<<< orphan*/  data; int /*<<< orphan*/  inUse; } ;
struct TYPE_11__ {size_t ncb_lsn; int /*<<< orphan*/  ncb_buffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* send ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;} ;
typedef  TYPE_3__* PNCB ;
typedef  TYPE_4__ NetBIOSSession ;
typedef  TYPE_5__ NetBIOSAdapter ;

/* Variables and functions */
 int /*<<< orphan*/  NRC_BADDR ; 
 int /*<<< orphan*/  NRC_BRIDGE ; 
 int /*<<< orphan*/  NRC_ILLCMD ; 
 int /*<<< orphan*/  NRC_INVADDRESS ; 
 int /*<<< orphan*/  NRC_SNUMOUT ; 
 scalar_t__ SESSION_ESTABLISHED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static UCHAR nbSend(NetBIOSAdapter *adapter, PNCB ncb)
{
    UCHAR ret;
    NetBIOSSession *session;

    if (!adapter) return NRC_BRIDGE;
    if (!adapter->transport->send) return NRC_ILLCMD;
    if (!ncb) return NRC_INVADDRESS;
    if (ncb->ncb_lsn >= adapter->sessionsLen) return NRC_SNUMOUT;
    if (!adapter->sessions[ncb->ncb_lsn].inUse) return NRC_SNUMOUT;
    if (!ncb->ncb_buffer) return NRC_BADDR;

    session = &adapter->sessions[ncb->ncb_lsn];
    if (session->state != SESSION_ESTABLISHED)
        ret = NRC_SNUMOUT;
    else
        ret = adapter->transport->send(adapter->impl.data, session->data, ncb);
    return ret;
}