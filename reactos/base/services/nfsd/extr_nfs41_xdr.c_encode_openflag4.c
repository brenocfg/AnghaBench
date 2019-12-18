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
struct TYPE_3__ {int opentype; int /*<<< orphan*/  how; } ;
typedef  TYPE_1__ openflag4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  OPEN4_CREATE 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  encode_createhow4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t encode_openflag4(
    XDR *xdr,
    openflag4 *of)
{
    bool_t result = TRUE;

    if (!xdr_u_int32_t(xdr, &of->opentype))
        return FALSE;

    switch (of->opentype)
    {
    case OPEN4_CREATE:
        result = encode_createhow4(xdr, &of->how);
        break;
    default:
        break;
    }
    return result;
}