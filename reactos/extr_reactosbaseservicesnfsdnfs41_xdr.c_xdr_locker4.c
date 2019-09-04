#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  lock_seqid; TYPE_3__* lock_stateid; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  lock_seqid; TYPE_1__* open_stateid; int /*<<< orphan*/  open_seqid; } ;
struct TYPE_18__ {TYPE_4__ lock_owner; TYPE_2__ open_owner; } ;
struct TYPE_19__ {TYPE_5__ u; scalar_t__ new_lock_owner; } ;
typedef  TYPE_6__ locker4 ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_20__ {scalar_t__ x_op; } ;
typedef  TYPE_7__ XDR ;
struct TYPE_16__ {int /*<<< orphan*/  stateid; } ;
struct TYPE_14__ {int /*<<< orphan*/  stateid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ XDR_ENCODE ; 
 int /*<<< orphan*/  eprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  xdr_bool (TYPE_7__*,scalar_t__*) ; 
 int /*<<< orphan*/  xdr_state_owner4 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_stateid4 (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (TYPE_7__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t xdr_locker4(
    XDR *xdr,
    locker4 *locker)
{
    if (xdr->x_op != XDR_ENCODE) {
        eprintf("%s: xdr->x_op %d is not supported!\n",
            "xdr_locker4", xdr->x_op);
        return FALSE;
    }

    if (!xdr_bool(xdr, &locker->new_lock_owner))
        return FALSE;

    if (locker->new_lock_owner) {
        /* open_to_lock_owner4 open_owner */
        if (!xdr_u_int32_t(xdr, &locker->u.open_owner.open_seqid))
            return FALSE;

        if (!xdr_stateid4(xdr, &locker->u.open_owner.open_stateid->stateid))
            return FALSE;

        if (!xdr_u_int32_t(xdr, &locker->u.open_owner.lock_seqid))
            return FALSE;

        return xdr_state_owner4(xdr, locker->u.open_owner.lock_owner);
    } else {
        /* exist_lock_owner4 lock_owner */
        if (!xdr_stateid4(xdr, &locker->u.lock_owner.lock_stateid->stateid))
            return FALSE;

        return xdr_u_int32_t(xdr, &locker->u.lock_owner.lock_seqid);
    }
}