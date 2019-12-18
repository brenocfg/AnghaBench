#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  args; int /*<<< orphan*/  type; } ;
struct cb_layoutrecall_args {TYPE_1__ recall; int /*<<< orphan*/  changed; int /*<<< orphan*/  iomode; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 int /*<<< orphan*/  NULL_xdrproc_t ; 
 int /*<<< orphan*/  cb_layoutrecall_discrim ; 
 scalar_t__ xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_union (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t op_cb_layoutrecall_args(XDR *xdr, struct cb_layoutrecall_args *args)
{
    bool_t result;

    result = xdr_enum(xdr, (enum_t*)&args->type);
    if (!result) { CBX_ERR("layoutrecall_args.type"); goto out; }

    result = xdr_enum(xdr, (enum_t*)&args->iomode);
    if (!result) { CBX_ERR("layoutrecall_args.iomode"); goto out; }

    result = xdr_bool(xdr, &args->changed);
    if (!result) { CBX_ERR("layoutrecall_args.changed"); goto out; }

    result = xdr_union(xdr, (enum_t*)&args->recall.type,
        (char*)&args->recall.args, cb_layoutrecall_discrim, NULL_xdrproc_t);
    if (!result) { CBX_ERR("layoutrecall_args.recall"); goto out; }
out:
    return result;
}