#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_14__ {int /*<<< orphan*/  nbname; int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  ncb_callname; } ;
struct TYPE_12__ {int /*<<< orphan*/  nameQueryXID; } ;
struct TYPE_11__ {int /*<<< orphan*/  ret; TYPE_4__* cacheEntry; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_1__ NetBTNameQueryData ;
typedef  TYPE_2__ NetBTAdapter ;
typedef  TYPE_3__ NCB ;
typedef  TYPE_4__ NBNameCacheEntry ;
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int GetTickCount () ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  NBNS_TYPE_NB ; 
 int /*<<< orphan*/  NCBNAMSZ ; 
 int /*<<< orphan*/  NCB_CANCELLED (TYPE_3__ const*) ; 
 int /*<<< orphan*/  NRC_BADDR ; 
 int /*<<< orphan*/  NRC_CMDCAN ; 
 int /*<<< orphan*/  NRC_GOODRET ; 
 int /*<<< orphan*/  NRC_SYSTEM ; 
 int /*<<< orphan*/  NetBTFindNameAnswerCallback ; 
 int NetBTSendNameQuery (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NetBTWaitForNameResponse (TYPE_2__ const*,scalar_t__,unsigned int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UCHAR NetBTNameWaitLoop(const NetBTAdapter *adapter, SOCKET fd, const NCB *ncb,
 DWORD sendTo, BOOL broadcast, DWORD timeout, DWORD maxQueries,
 NBNameCacheEntry **cacheEntry)
{
    unsigned int queries;
    NetBTNameQueryData queryData;

    if (!adapter) return NRC_BADDR;
    if (fd == INVALID_SOCKET) return NRC_BADDR;
    if (!ncb) return NRC_BADDR;
    if (!cacheEntry) return NRC_BADDR;

    queryData.cacheEntry = NULL;
    queryData.ret = NRC_GOODRET;
    for (queries = 0; queryData.cacheEntry == NULL && queries < maxQueries;
     queries++)
    {
        if (!NCB_CANCELLED(ncb))
        {
            int r = NetBTSendNameQuery(fd, ncb->ncb_callname,
             adapter->nameQueryXID, NBNS_TYPE_NB, sendTo, broadcast);

            if (r == 0)
                queryData.ret = NetBTWaitForNameResponse(adapter, fd,
                 GetTickCount() + timeout, NetBTFindNameAnswerCallback,
                 &queryData);
            else
                queryData.ret = NRC_SYSTEM;
        }
        else
            queryData.ret = NRC_CMDCAN;
    }
    if (queryData.cacheEntry)
    {
        memcpy(queryData.cacheEntry->name, ncb->ncb_callname, NCBNAMSZ);
        memcpy(queryData.cacheEntry->nbname, ncb->ncb_callname, NCBNAMSZ);
    }
    *cacheEntry = queryData.cacheEntry;
    return queryData.ret;
}