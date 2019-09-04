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
struct TYPE_3__ {unsigned char* co_ownerid; int /*<<< orphan*/  co_ownerid_len; int /*<<< orphan*/ * co_verifier; } ;
typedef  TYPE_1__ client_owner4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  NFS4_VERIFIER_SIZE ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_opaque (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t xdr_client_owner4(
    XDR *xdr,
    client_owner4 *co)
{
    unsigned char *co_ownerid = co->co_ownerid;
    if (!xdr_opaque(xdr, (char *)&co->co_verifier[0], NFS4_VERIFIER_SIZE))
        return FALSE;

    return xdr_bytes(xdr, (char **)&co_ownerid, &co->co_ownerid_len, NFS4_OPAQUE_LIMIT);
}