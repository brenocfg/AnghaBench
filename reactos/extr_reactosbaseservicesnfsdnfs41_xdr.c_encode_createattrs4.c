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
typedef  int /*<<< orphan*/  nfs41_file_info ;
struct TYPE_4__ {int /*<<< orphan*/  attr_vals_len; } ;
typedef  TYPE_1__ fattr4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  encode_file_attrs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_fattr4 (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static bool_t encode_createattrs4(
    XDR *xdr,
    nfs41_file_info* createattrs)
{
    fattr4 attrs;

    /* encode attribute values from createattrs->info into attrs.attr_vals */
    attrs.attr_vals_len = NFS4_OPAQUE_LIMIT;
    if (!encode_file_attrs(&attrs, createattrs))
        return FALSE;

    return xdr_fattr4(xdr, &attrs);
}