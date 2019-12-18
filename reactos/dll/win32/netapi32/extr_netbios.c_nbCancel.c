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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  inUse; } ;
struct TYPE_10__ {size_t sessionsLen; int /*<<< orphan*/  cmdQueue; TYPE_4__* sessions; } ;
struct TYPE_9__ {int ncb_command; size_t ncb_lsn; } ;
typedef  TYPE_1__* PNCB ;
typedef  TYPE_2__ NetBIOSAdapter ;

/* Variables and functions */
 int /*<<< orphan*/  NBCmdQueueCancel (int /*<<< orphan*/ ,TYPE_1__*) ; 
#define  NCBADDGRNAME 139 
#define  NCBADDNAME 138 
#define  NCBCALL 137 
#define  NCBCANCEL 136 
#define  NCBCHAINSEND 135 
#define  NCBCHAINSENDNA 134 
#define  NCBDELNAME 133 
#define  NCBHANGUP 132 
#define  NCBRESET 131 
#define  NCBSEND 130 
#define  NCBSENDNA 129 
#define  NCBSSTAT 128 
 int /*<<< orphan*/  NRC_BRIDGE ; 
 int /*<<< orphan*/  NRC_CANCEL ; 
 int /*<<< orphan*/  NRC_CANOCCR ; 
 int /*<<< orphan*/  NRC_CMDCAN ; 
 int /*<<< orphan*/  NRC_INVADDRESS ; 
 int /*<<< orphan*/  NRC_SNUMOUT ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  nbInternalHangup (TYPE_2__*,TYPE_4__*) ; 

__attribute__((used)) static UCHAR nbCancel(NetBIOSAdapter *adapter, PNCB ncb)
{
    UCHAR ret;

    TRACE(": adapter %p, ncb %p\n", adapter, ncb);

    if (!adapter) return NRC_BRIDGE;
    if (!ncb) return NRC_INVADDRESS;

    switch (ncb->ncb_command & 0x7f)
    {
        case NCBCANCEL:
        case NCBADDNAME:
        case NCBADDGRNAME:
        case NCBDELNAME:
        case NCBRESET:
        case NCBSSTAT:
            ret = NRC_CANCEL;
            break;

        /* NCBCALL, NCBCHAINSEND/NCBSEND, NCBHANGUP all close the associated
         * session if cancelled */
        case NCBCALL:
        case NCBSEND:
        case NCBCHAINSEND:
        case NCBSENDNA:
        case NCBCHAINSENDNA:
        case NCBHANGUP:
        {
            if (ncb->ncb_lsn >= adapter->sessionsLen)
                ret = NRC_SNUMOUT;
            else if (!adapter->sessions[ncb->ncb_lsn].inUse)
                ret = NRC_SNUMOUT;
            else
            {
                ret = NBCmdQueueCancel(adapter->cmdQueue, ncb);
                if (ret == NRC_CMDCAN || ret == NRC_CANOCCR)
                    nbInternalHangup(adapter, &adapter->sessions[ncb->ncb_lsn]);
            }
            break;
        }

        default:
            ret = NBCmdQueueCancel(adapter->cmdQueue, ncb);
    }
    TRACE("returning 0x%02x\n", ret);
    return ret;
}