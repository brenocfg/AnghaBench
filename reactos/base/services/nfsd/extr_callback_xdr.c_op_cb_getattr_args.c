#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cb_getattr_args {int /*<<< orphan*/  attr_request; int /*<<< orphan*/  fh; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 scalar_t__ common_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_bitmap4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t op_cb_getattr_args(XDR *xdr, struct cb_getattr_args *args)
{
    bool_t result;

    result = common_fh(xdr, &args->fh);
    if (!result) { CBX_ERR("getattr.fh"); goto out; }

    result = xdr_bitmap4(xdr, &args->attr_request);
    if (!result) { CBX_ERR("getattr.attr_request"); goto out; }
out:
    return result;
}