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
struct TYPE_13__ {int /*<<< orphan*/  sessionsLen; TYPE_1__ impl; TYPE_2__* transport; } ;
struct TYPE_12__ {int /*<<< orphan*/  max_cfg_sess; int /*<<< orphan*/  max_sess; } ;
struct TYPE_11__ {int ncb_length; char* ncb_callname; int /*<<< orphan*/  ncb_buffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* astat ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
typedef  TYPE_3__* PNCB ;
typedef  TYPE_4__* PADAPTER_STATUS ;
typedef  TYPE_5__ NetBIOSAdapter ;
typedef  int /*<<< orphan*/  ADAPTER_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NRC_BADDR ; 
 int /*<<< orphan*/  NRC_BRIDGE ; 
 int /*<<< orphan*/  NRC_BUFLEN ; 
 int /*<<< orphan*/  NRC_ILLCMD ; 
 int /*<<< orphan*/  NRC_INVADDRESS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static UCHAR nbAStat(NetBIOSAdapter *adapter, PNCB ncb)
{
    UCHAR ret;

    if (!adapter) return NRC_BRIDGE;
    if (!adapter->transport->astat) return NRC_ILLCMD;
    if (!ncb) return NRC_INVADDRESS;
    if (!ncb->ncb_buffer) return NRC_BADDR;
    if (ncb->ncb_length < sizeof(ADAPTER_STATUS)) return NRC_BUFLEN;

    ret = adapter->transport->astat(adapter->impl.data, ncb);
    if (ncb->ncb_callname[0] == '*')
    {
        PADAPTER_STATUS astat = (PADAPTER_STATUS)ncb->ncb_buffer;

        astat->max_sess = astat->max_cfg_sess = adapter->sessionsLen;
    }
    return ret;
}