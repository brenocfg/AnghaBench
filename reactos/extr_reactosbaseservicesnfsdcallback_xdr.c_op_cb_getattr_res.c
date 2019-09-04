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
struct cb_getattr_res {scalar_t__ status; int /*<<< orphan*/  info; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ fattr4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 scalar_t__ NFS4_OK ; 
 int /*<<< orphan*/  info_to_fattr4 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  xdr_fattr4 (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static bool_t op_cb_getattr_res(XDR *xdr, struct cb_getattr_res *res)
{
    bool_t result;

    result = xdr_enum(xdr, &res->status);
    if (!result) { CBX_ERR("getattr.status"); goto out; }

    if (res->status == NFS4_OK) {
        fattr4 fattr = { 0 };

        result = info_to_fattr4(&res->info, &fattr);
        if (!result) { goto out; }

        result = xdr_fattr4(xdr, &fattr);
        if (!result) { CBX_ERR("getattr.obj_attributes"); goto out; }
    }
out:
    return result;
}