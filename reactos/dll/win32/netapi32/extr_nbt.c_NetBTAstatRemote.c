#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_19__ {scalar_t__ numAddresses; int /*<<< orphan*/ * addresses; } ;
struct TYPE_18__ {int /*<<< orphan*/  nameQueryXID; } ;
struct TYPE_17__ {int /*<<< orphan*/  gotResponse; int /*<<< orphan*/  astatLen; TYPE_2__* astat; } ;
struct TYPE_16__ {scalar_t__ name_count; } ;
struct TYPE_15__ {int /*<<< orphan*/  ncb_callname; int /*<<< orphan*/  ncb_length; int /*<<< orphan*/  ncb_buffer; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_1__* PNCB ;
typedef  TYPE_2__* PADAPTER_STATUS ;
typedef  TYPE_3__ NetBTNodeQueryData ;
typedef  TYPE_4__ NetBTAdapter ;
typedef  TYPE_5__ NBNameCacheEntry ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetTickCount () ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  NBNS_TYPE_NBSTAT ; 
 int /*<<< orphan*/  NCB_CANCELLED (TYPE_1__*) ; 
 int /*<<< orphan*/  NRC_BADDR ; 
 int /*<<< orphan*/  NRC_CMDCAN ; 
 int /*<<< orphan*/  NRC_CMDTMO ; 
 int /*<<< orphan*/  NRC_GOODRET ; 
 int /*<<< orphan*/  NRC_INVADDRESS ; 
 int /*<<< orphan*/  NRC_OSRESNOTAV ; 
 int /*<<< orphan*/  NRC_SYSTEM ; 
 int /*<<< orphan*/  NetBTInternalFindName (TYPE_4__*,TYPE_1__*,TYPE_5__ const**) ; 
 int /*<<< orphan*/  NetBTNodeStatusAnswerCallback ; 
 int NetBTSendNameQuery (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NetBTWaitForNameResponse (TYPE_4__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*,...) ; 
 scalar_t__ WSASocketA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSA_FLAG_OVERLAPPED ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ gWINSQueries ; 
 scalar_t__ gWINSQueryTimeout ; 

__attribute__((used)) static UCHAR NetBTAstatRemote(NetBTAdapter *adapter, PNCB ncb)
{
    UCHAR ret = NRC_GOODRET;
    const NBNameCacheEntry *cacheEntry = NULL;

    TRACE("adapter %p, NCB %p\n", adapter, ncb);

    if (!adapter) return NRC_BADDR;
    if (!ncb) return NRC_INVADDRESS;

    ret = NetBTInternalFindName(adapter, ncb, &cacheEntry);
    if (ret == NRC_GOODRET && cacheEntry)
    {
        if (cacheEntry->numAddresses > 0)
        {
            SOCKET fd = WSASocketA(PF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0,
             WSA_FLAG_OVERLAPPED);

            if(fd == INVALID_SOCKET)
                ret = NRC_OSRESNOTAV;
            else
            {
                NetBTNodeQueryData queryData;
                DWORD queries;
                PADAPTER_STATUS astat = (PADAPTER_STATUS)ncb->ncb_buffer;

                adapter->nameQueryXID++;
                astat->name_count = 0;
                queryData.gotResponse = FALSE;
                queryData.astat = astat;
                queryData.astatLen = ncb->ncb_length;
                for (queries = 0; !queryData.gotResponse &&
                 queries < gWINSQueries; queries++)
                {
                    if (!NCB_CANCELLED(ncb))
                    {
                        int r = NetBTSendNameQuery(fd, ncb->ncb_callname,
                         adapter->nameQueryXID, NBNS_TYPE_NBSTAT,
                         cacheEntry->addresses[0], FALSE);

                        if (r == 0)
                            ret = NetBTWaitForNameResponse(adapter, fd,
                             GetTickCount() + gWINSQueryTimeout,
                             NetBTNodeStatusAnswerCallback, &queryData);
                        else
                            ret = NRC_SYSTEM;
                    }
                    else
                        ret = NRC_CMDCAN;
                }
                closesocket(fd);
            }
        }
        else
            ret = NRC_CMDTMO;
    }
    else if (ret == NRC_CMDCAN)
        ; /* do nothing, we were cancelled */
    else
        ret = NRC_CMDTMO;
    TRACE("returning 0x%02x\n", ret);
    return ret;
}