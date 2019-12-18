#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_4__ {scalar_t__ x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XDR_DECODE ; 
 int /*<<< orphan*/  eprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  xdr_u_int32_t (TYPE_1__*,scalar_t__*) ; 

__attribute__((used)) static bool_t xdr_layout_types(
    XDR *xdr,
    uint32_t *layout_type)
{
    u_int32_t i, count, type;

    if (xdr->x_op != XDR_DECODE) {
        eprintf("xdr_layout_types: xdr->x_op is not XDR_DECODE! "
            "x_op %d not supported.\n", xdr->x_op);
        return FALSE;
    }

    *layout_type = 0;

    if (!xdr_u_int32_t(xdr, &count))
        return FALSE;

    for (i = 0; i < count; i++) {
        if (!xdr_u_int32_t(xdr, &type))
            return FALSE;

        *layout_type |= 1 << (type - 1);
    }
    return TRUE;
}