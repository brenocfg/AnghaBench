#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stateid_arg ;
struct TYPE_8__ {scalar_t__ out_len; int /*<<< orphan*/  len; int /*<<< orphan*/  buffer; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ readwrite_upcall_args ;
struct TYPE_7__ {TYPE_2__ rw; } ;
struct TYPE_9__ {int /*<<< orphan*/  state_ref; TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int ERROR_HANDLE_EOF ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  nfs41_open_stateid_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read_from_mds (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int read_from_pnfs (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_read(nfs41_upcall *upcall)
{
    readwrite_upcall_args *args = &upcall->args.rw;
    stateid_arg stateid;
    ULONG pnfs_bytes_read = 0;
    int status = NO_ERROR;

    nfs41_open_stateid_arg(upcall->state_ref, &stateid);

#ifdef PNFS_ENABLE_READ
    status = read_from_pnfs(upcall, &stateid);

    if (status == NO_ERROR || status == ERROR_HANDLE_EOF)
        goto out;

    if (args->out_len) {
        pnfs_bytes_read = args->out_len;
        args->out_len = 0;

        args->offset += pnfs_bytes_read;
        args->buffer += pnfs_bytes_read;
        args->len -= pnfs_bytes_read;
    }
#endif

    status = read_from_mds(upcall, &stateid);

    args->out_len += pnfs_bytes_read;
out:
    return status;
}