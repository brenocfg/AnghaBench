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
typedef  int uint32_t ;
struct TYPE_6__ {int stamp; int /*<<< orphan*/  machinename; } ;
struct TYPE_5__ {TYPE_2__ auth_sys; } ;
struct TYPE_7__ {int type; TYPE_1__ u; } ;
typedef  TYPE_3__ nfs41_callback_secparms ;
typedef  int bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
#define  AUTH_NONE 130 
#define  AUTH_SYS 129 
 int FALSE ; 
 int /*<<< orphan*/  NI_MAXHOST ; 
#define  RPCSEC_GSS 128 
 int TRUE ; 
 int /*<<< orphan*/  xdr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_int32_t (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t encode_backchannel_sec_parms(
    XDR *xdr,
    nfs41_callback_secparms *args)
{
    uint32_t zero = 0;

    if (!xdr_u_int32_t(xdr, &args->type))
        return FALSE;

    switch (args->type)  {
    case AUTH_NONE: return TRUE;
    case AUTH_SYS:
        if (!xdr_u_int32_t(xdr, &args->u.auth_sys.stamp))
            return FALSE;
        if (!xdr_string(xdr, &args->u.auth_sys.machinename, NI_MAXHOST))
            return FALSE;
        return xdr_u_int32_t(xdr, &zero) && xdr_u_int32_t(xdr, &zero) && 
                xdr_u_int32_t(xdr, &zero);
    case RPCSEC_GSS:
    default:
        return FALSE;
    }
}