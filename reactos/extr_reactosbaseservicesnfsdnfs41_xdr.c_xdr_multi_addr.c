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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  netaddr4 ;
struct TYPE_3__ {size_t count; int /*<<< orphan*/ * arr; } ;
typedef  TYPE_1__ multi_addr4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t NFS41_ADDRS_PER_SERVER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_pnfs_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static bool_t xdr_multi_addr(
    XDR *xdr,
    multi_addr4 *list)
{
    netaddr4 dummy, *dest;
    uint32_t i;

    if (!xdr_u_int32_t(xdr, &list->count))
        return FALSE;

    for (i = 0; i < list->count; i++) {
        /* if there are too many addrs, decode the extras into 'dummy' */
        dest = i < NFS41_ADDRS_PER_SERVER ? &list->arr[i] : &dummy;

        if (!xdr_pnfs_addr(xdr, dest))
            return FALSE;
    }
    return TRUE;
}