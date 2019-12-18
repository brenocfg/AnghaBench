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
struct cb_recall_args {int /*<<< orphan*/  fh; int /*<<< orphan*/  truncate; int /*<<< orphan*/  stateid; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 scalar_t__ common_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ common_stateid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t op_cb_recall_args(XDR *xdr, struct cb_recall_args *args)
{
    bool_t result;

    result = common_stateid(xdr, &args->stateid);
    if (!result) { CBX_ERR("recall.stateid"); goto out; }

    result = xdr_bool(xdr, &args->truncate);
    if (!result) { CBX_ERR("recall.truncate"); goto out; }

    result = common_fh(xdr, &args->fh);
    if (!result) { CBX_ERR("recall.fh"); goto out; }
out:
    return result;
}