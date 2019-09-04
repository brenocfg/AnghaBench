#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_7__ {size_t count; TYPE_2__* arr; } ;
typedef  TYPE_1__ pnfs_data_server_list ;
struct TYPE_8__ {int /*<<< orphan*/  addrs; int /*<<< orphan*/  lock; int /*<<< orphan*/ * client; } ;
typedef  TYPE_2__ pnfs_data_server ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeSRWLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,size_t) ; 
 TYPE_2__* realloc (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  xdr_multi_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static bool_t xdr_data_server_list(
    XDR *xdr,
    pnfs_data_server_list *servers)
{
    uint32_t i, count;

    if (!xdr_u_int32_t(xdr, &count))
        return FALSE;

    if (count && count != servers->count) {
        pnfs_data_server *tmp;
        /* clear data server clients; they're still cached with nfs41_root,
         * so pnfs_data_server_client() will look them up again */
        for (i = 0; i < servers->count; i++)
            servers->arr[i].client = NULL;

        tmp = realloc(servers->arr, count * sizeof(pnfs_data_server));
        if (tmp == NULL) 
            return FALSE;
        servers->arr = tmp;
        ZeroMemory(servers->arr, count * sizeof(pnfs_data_server));
        for (i = servers->count; i < count; i++) /* initialize new elements */
            InitializeSRWLock(&servers->arr[i].lock);
        servers->count = count;
    }

    for (i = 0; i < servers->count; i++) {
        if (!xdr_multi_addr(xdr, &servers->arr[i].addrs))
            return FALSE;
    }
    return TRUE;
}