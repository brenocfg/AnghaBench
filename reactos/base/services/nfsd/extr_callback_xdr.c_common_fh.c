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
struct TYPE_3__ {scalar_t__ len; scalar_t__ fh; } ;
typedef  TYPE_1__ nfs41_fh ;
typedef  int bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 scalar_t__ NFS4_FHSIZE ; 
 scalar_t__ xdr_opaque (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ xdr_u_int32_t (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bool_t common_fh(XDR *xdr, nfs41_fh *fh)
{
    return xdr_u_int32_t(xdr, &fh->len)
        && fh->len <= NFS4_FHSIZE
        && xdr_opaque(xdr, (char*)fh->fh, fh->len);
}