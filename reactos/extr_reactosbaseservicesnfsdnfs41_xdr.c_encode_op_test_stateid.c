#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  stateid_arg ;
struct TYPE_4__ {int /*<<< orphan*/  op; scalar_t__ arg; } ;
typedef  TYPE_1__ nfs_argop4 ;
struct TYPE_5__ {int /*<<< orphan*/  count; int /*<<< orphan*/  stateids; } ;
typedef  TYPE_2__ nfs41_test_stateid_args ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_TEST_STATEID ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_array (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_stateid4 ; 

__attribute__((used)) static bool_t encode_op_test_stateid(
    XDR *xdr,
    nfs_argop4 *argop)
{
    nfs41_test_stateid_args *args = (nfs41_test_stateid_args*)argop->arg;

    if (unexpected_op(argop->op, OP_TEST_STATEID))
        return FALSE;

    return xdr_array(xdr, (char**)&args->stateids, &args->count,
        args->count, sizeof(stateid_arg), (xdrproc_t)xdr_stateid4);
}