#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  op; scalar_t__ res; } ;
typedef  TYPE_2__ nfs_resop4 ;
struct TYPE_5__ {int /*<<< orphan*/  count; int /*<<< orphan*/  status; } ;
struct TYPE_7__ {scalar_t__ status; TYPE_1__ resok; } ;
typedef  TYPE_3__ nfs41_test_stateid_res ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NFS4_OK ; 
 int /*<<< orphan*/  OP_TEST_STATEID ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_array (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bool_t decode_op_test_stateid(
    XDR *xdr,
    nfs_resop4 *resop)
{
    nfs41_test_stateid_res *res = (nfs41_test_stateid_res*)resop->res;

    if (unexpected_op(resop->op, OP_TEST_STATEID))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &res->status))
        return FALSE;

    if (res->status == NFS4_OK) {
        return xdr_array(xdr, (char**)&res->resok.status, &res->resok.count,
            res->resok.count, sizeof(uint32_t), (xdrproc_t)xdr_u_int32_t);
    }
    return TRUE;
}