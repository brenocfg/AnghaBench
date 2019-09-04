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
typedef  size_t uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* encode ) (int /*<<< orphan*/ *,TYPE_3__*) ;} ;
typedef  TYPE_1__ op_table_entry ;
struct TYPE_6__ {unsigned char* tag; size_t minorversion; size_t argarray_count; TYPE_3__* argarray; int /*<<< orphan*/  tag_len; } ;
typedef  TYPE_2__ nfs41_compound_args ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_7__ {size_t op; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* op_table_find (size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,size_t*) ; 

bool_t nfs_encode_compound(
    XDR *xdr,
    caddr_t *pargs)
{
    unsigned char *tag;

    nfs41_compound_args *args = (nfs41_compound_args*)pargs;
    uint32_t i;
    const op_table_entry *entry;

    tag = args->tag;
    if (!xdr_bytes(xdr, (char **)&tag, &args->tag_len, NFS4_OPAQUE_LIMIT))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &args->minorversion))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &args->argarray_count))
        return FALSE;

    for (i = 0; i < args->argarray_count; i++)
    {
        entry = op_table_find(args->argarray[i].op);
        if (entry == NULL || entry->encode == NULL)
            return FALSE;

        if (!xdr_u_int32_t(xdr, &args->argarray[i].op))
            return FALSE;
        if (!entry->encode(xdr, &args->argarray[i]))
            return FALSE;
    }
    return TRUE;
}