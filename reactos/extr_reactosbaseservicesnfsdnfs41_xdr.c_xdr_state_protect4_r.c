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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int spr_how; } ;
typedef  TYPE_1__ state_protect4_r ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  SP4_NONE 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t xdr_state_protect4_r(
    XDR *xdr,
    state_protect4_r *spr)
{
    bool_t result = TRUE;

    if (!xdr_u_int32_t(xdr, (uint32_t *)&spr->spr_how))
        return FALSE;

    switch (spr->spr_how)
    {
    case SP4_NONE:
        break;
#if 0
    case SP4_MACH_CRED:
        result = decode_state_protect_ops4(xdr, &spr->u.spr_mach_ops);
        break;
    case SP4_SSV:
        result = decode_ssv_prot_info4(xdr, &spr->u.spr_ssv_info);
        break;
#endif
    default:
        eprintf("decode_state_protect4_r: state protect "
            "type %d not supported.\n", spr->spr_how);
        result = FALSE;
        break;
    }
    return result;
}