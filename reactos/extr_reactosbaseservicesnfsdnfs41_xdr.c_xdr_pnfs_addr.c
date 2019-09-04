#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {char* netid; char* uaddr; } ;
typedef  TYPE_1__ netaddr4 ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_7__ {scalar_t__ x_op; } ;
typedef  TYPE_2__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t NFS41_NETWORK_ID_LEN ; 
 size_t NFS41_UNIVERSAL_ADDR_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XDR_DECODE ; 
 scalar_t__ XDR_ENCODE ; 
 int /*<<< orphan*/  xdr_bytes (TYPE_2__*,char**,size_t*,size_t) ; 

__attribute__((used)) static bool_t xdr_pnfs_addr(
    XDR *xdr,
    netaddr4 *addr)
{
    uint32_t len;
    char *netid = addr->netid;
    char *uaddr = addr->uaddr;

    if (xdr->x_op == XDR_ENCODE)
        len = sizeof(addr->netid);
    if (!xdr_bytes(xdr, &netid, &len, NFS41_NETWORK_ID_LEN))
        return FALSE;

    if (xdr->x_op == XDR_DECODE) {
        if (len < NFS41_NETWORK_ID_LEN)
            addr->netid[len] = 0;
        else
            addr->netid[NFS41_NETWORK_ID_LEN] = 0;
    }

    if (xdr->x_op == XDR_ENCODE)
        len = sizeof(addr->uaddr);
    if (!xdr_bytes(xdr, &uaddr, &len, NFS41_UNIVERSAL_ADDR_LEN))
        return FALSE;

    if (xdr->x_op == XDR_DECODE){
        if (len < NFS41_UNIVERSAL_ADDR_LEN)
            addr->uaddr[len] = 0;
        else
            addr->uaddr[NFS41_UNIVERSAL_ADDR_LEN] = 0;
    }

    return TRUE;
}