#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  filename; } ;
struct TYPE_16__ {TYPE_5__* delegate_stateid; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; TYPE_3__* delegate_stateid; } ;
struct TYPE_12__ {int delegate_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  filename; } ;
struct TYPE_18__ {TYPE_7__ deleg_prev; TYPE_6__ deleg_cur_fh; TYPE_4__ deleg_cur; TYPE_2__ prev; TYPE_1__ null; } ;
struct TYPE_19__ {int claim; TYPE_8__ u; } ;
typedef  TYPE_9__ open_claim4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_15__ {int /*<<< orphan*/  stateid; } ;
struct TYPE_13__ {int /*<<< orphan*/  stateid; } ;

/* Variables and functions */
#define  CLAIM_DELEGATE_CUR 134 
#define  CLAIM_DELEGATE_PREV 133 
#define  CLAIM_DELEG_CUR_FH 132 
#define  CLAIM_DELEG_PREV_FH 131 
#define  CLAIM_FH 130 
#define  CLAIM_NULL 129 
#define  CLAIM_PREVIOUS 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  encode_claim_deleg_cur (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_component (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  xdr_stateid4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t encode_open_claim4(
    XDR *xdr,
    open_claim4 *oc)
{
    if (!xdr_u_int32_t(xdr, &oc->claim))
        return FALSE;

    switch (oc->claim)
    {
    case CLAIM_NULL:
        return encode_component(xdr, oc->u.null.filename);
    case CLAIM_PREVIOUS:
        return xdr_u_int32_t(xdr, &oc->u.prev.delegate_type);
    case CLAIM_FH:
        return TRUE; /* use current file handle */
    case CLAIM_DELEGATE_CUR:
        return encode_claim_deleg_cur(xdr,
            &oc->u.deleg_cur.delegate_stateid->stateid,
            oc->u.deleg_cur.name);
    case CLAIM_DELEG_CUR_FH:
        return xdr_stateid4(xdr,
            &oc->u.deleg_cur_fh.delegate_stateid->stateid);
    case CLAIM_DELEGATE_PREV:
        return encode_component(xdr, oc->u.deleg_prev.filename);
    case CLAIM_DELEG_PREV_FH:
        return TRUE; /* use current file handle */
    default:
        eprintf("encode_open_claim4: unsupported claim %d.\n",
            oc->claim);
        return FALSE;
    }
}