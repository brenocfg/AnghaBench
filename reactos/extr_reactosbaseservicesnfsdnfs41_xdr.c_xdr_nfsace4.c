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
struct TYPE_7__ {char* who; int /*<<< orphan*/  acemask; int /*<<< orphan*/  aceflag; int /*<<< orphan*/  acetype; } ;
typedef  TYPE_1__ nfsace4 ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_8__ {scalar_t__ x_op; } ;
typedef  TYPE_2__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XDR_FREE ; 
 int /*<<< orphan*/  xdr_string (TYPE_2__*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t xdr_nfsace4(
    XDR *xdr,
    nfsace4 *ace)
{
    char *who = ace->who;

    if (!xdr_u_int32_t(xdr, &ace->acetype))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &ace->aceflag))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &ace->acemask))
        return FALSE;

    /* 'who' is a static array, so don't try to free it */
    if (xdr->x_op == XDR_FREE)
        return TRUE;

    return xdr_string(xdr, &who, NFS4_OPAQUE_LIMIT);
}