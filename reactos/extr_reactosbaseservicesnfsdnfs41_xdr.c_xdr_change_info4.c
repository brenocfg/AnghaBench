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
struct TYPE_3__ {int /*<<< orphan*/  after; int /*<<< orphan*/  before; int /*<<< orphan*/  atomic; } ;
typedef  TYPE_1__ change_info4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t xdr_change_info4(
    XDR *xdr,
    change_info4 *cinfo)
{
    if (!xdr_bool(xdr, &cinfo->atomic))
        return FALSE;

    if (!xdr_u_hyper(xdr, &cinfo->before))
        return FALSE;

    return xdr_u_hyper(xdr, &cinfo->after);
}