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
struct TYPE_3__ {char* so_major_id; int /*<<< orphan*/  so_major_id_len; int /*<<< orphan*/  so_minor_id; } ;
typedef  TYPE_1__ server_owner4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t xdr_server_owner4(
    XDR *xdr,
    server_owner4 *so)
{
    char *so_major_id = so->so_major_id;

    if (!xdr_u_hyper(xdr, &so->so_minor_id))
        return FALSE;

    return xdr_bytes(xdr, (char **)&so_major_id,
        &so->so_major_id_len, NFS4_OPAQUE_LIMIT);
}