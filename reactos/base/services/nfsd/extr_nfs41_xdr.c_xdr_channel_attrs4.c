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
typedef  int uint32_t ;
typedef  int u_int32_t ;
struct TYPE_6__ {int ca_headerpadsize; int ca_maxrequestsize; int ca_maxresponsesize; int ca_maxresponsesize_cached; int ca_maxoperations; int ca_maxrequests; int* ca_rdma_ird; } ;
typedef  TYPE_1__ nfs41_channel_attrs ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_7__ {scalar_t__ x_op; } ;
typedef  TYPE_2__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XDR_DECODE ; 
 scalar_t__ XDR_ENCODE ; 
 int /*<<< orphan*/  eprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  xdr_u_int32_t (TYPE_2__*,int*) ; 

__attribute__((used)) static bool_t xdr_channel_attrs4(
    XDR *xdr,
    nfs41_channel_attrs *attrs)
{
    uint32_t zero = 0;
    uint32_t one = 1;

    /* count4 ca_headerpadsize */
    if (!xdr_u_int32_t(xdr, &attrs->ca_headerpadsize))
        return FALSE;

    /* count4 ca_maxrequestsize */
    if (!xdr_u_int32_t(xdr, &attrs->ca_maxrequestsize))
        return FALSE;

    /* count4 ca_maxresponsesize */
    if (!xdr_u_int32_t(xdr, &attrs->ca_maxresponsesize))
        return FALSE;

    /* count4 ca_maxresponsesize_cached */
    if (!xdr_u_int32_t(xdr, &attrs->ca_maxresponsesize_cached))
        return FALSE;

    /* count4 ca_maxoperations */
    if (!xdr_u_int32_t(xdr, &attrs->ca_maxoperations))
        return FALSE;

    /* count4 ca_maxrequests */
    if (!xdr_u_int32_t(xdr, &attrs->ca_maxrequests))
        return FALSE;

    if (xdr->x_op == XDR_ENCODE) {
        /* uint32_t ca_rdma_ird<1> */
        if (attrs->ca_rdma_ird)
        {
            if (!xdr_u_int32_t(xdr, &one))
                return FALSE;
            return xdr_u_int32_t(xdr, attrs->ca_rdma_ird);
        }
        else {
            return xdr_u_int32_t(xdr, &zero);
        }
    }
    else if (xdr->x_op == XDR_DECODE) {
#if 0
        u_int32_t count;
        /* uint32_t ca_rdma_ird<1> */
        if (!xdr_u_int32_t(xdr, &count))
            return FALSE;
        if (count > 1)
            return FALSE;
        if (count)
            return xdr_u_int32_t(xdr, attrs->ca_rdma_ird);
        else
#endif
            return TRUE;
    }
    else {
        eprintf("%s: xdr->x_op %d not supported.\n",
            "xdr_channel_attrs4", xdr->x_op);
        return FALSE;
    }
}