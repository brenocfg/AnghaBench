#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  attrmask; int /*<<< orphan*/  change; } ;
typedef  TYPE_1__ nfs41_file_info ;
struct TYPE_6__ {int /*<<< orphan*/  attr_vals_len; int /*<<< orphan*/  attrmask; scalar_t__ attr_vals; } ;
typedef  TYPE_2__ fattr4 ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 int /*<<< orphan*/  FATTR4_WORD0_CHANGE ; 
 int /*<<< orphan*/  FATTR4_WORD0_SIZE ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 scalar_t__ bitmap_isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_getpos (int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t info_to_fattr4(nfs41_file_info *info, fattr4 *fattr)
{
    XDR fattr_xdr;
    bool_t result = TRUE;

    /* encode nfs41_file_info into fattr4 */
    xdrmem_create(&fattr_xdr, (char*)fattr->attr_vals,
        NFS4_OPAQUE_LIMIT, XDR_ENCODE);
    
    /* The only attributes that the server can reliably
     * query via CB_GETATTR are size and change. */
    if (bitmap_isset(&info->attrmask, 0, FATTR4_WORD0_CHANGE)) {
        result = xdr_u_hyper(&fattr_xdr, &info->change);
        if (!result) { CBX_ERR("getattr.info.change"); goto out; }
        bitmap_set(&fattr->attrmask, 0, FATTR4_WORD0_CHANGE);
    }
    if (bitmap_isset(&info->attrmask, 0, FATTR4_WORD0_SIZE)) {
        result = xdr_u_hyper(&fattr_xdr, &info->size);
        if (!result) { CBX_ERR("getattr.info.size"); goto out; }
        bitmap_set(&fattr->attrmask, 0, FATTR4_WORD0_SIZE);
    }
    fattr->attr_vals_len = xdr_getpos(&fattr_xdr);
out:
    return result;
}