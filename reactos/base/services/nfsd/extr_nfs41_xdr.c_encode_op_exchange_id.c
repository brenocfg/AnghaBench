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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  op; scalar_t__ arg; } ;
typedef  TYPE_1__ nfs_argop4 ;
struct TYPE_5__ {int eia_flags; scalar_t__ eia_client_impl_id; int /*<<< orphan*/  eia_state_protect; int /*<<< orphan*/  eia_clientowner; } ;
typedef  TYPE_2__ nfs41_exchange_id_args ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_EXCHANGE_ID ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_client_owner4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_nfs_impl_id4 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xdr_state_protect4_a (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t encode_op_exchange_id(
    XDR *xdr,
    nfs_argop4 *argop)
{
    uint32_t zero = 0;
    uint32_t one = 1;

    nfs41_exchange_id_args *args = (nfs41_exchange_id_args*)argop->arg;

    if (unexpected_op(argop->op, OP_EXCHANGE_ID))
        return FALSE;

    if (!xdr_client_owner4(xdr, args->eia_clientowner))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &args->eia_flags))
        return FALSE;

    if (!xdr_state_protect4_a(xdr, &args->eia_state_protect))
        return FALSE;

    if (args->eia_client_impl_id)
    {
        if (!xdr_u_int32_t(xdr, &one))
            return FALSE;
        return xdr_nfs_impl_id4(xdr, args->eia_client_impl_id);
    }
    else
        return xdr_u_int32_t(xdr, &zero);
}