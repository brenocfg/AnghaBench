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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  stateid_arg ;
struct TYPE_8__ {scalar_t__ out_len; scalar_t__ len; int /*<<< orphan*/  buffer; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ readwrite_upcall_args ;
struct TYPE_7__ {TYPE_2__ rw; } ;
struct TYPE_9__ {int /*<<< orphan*/  state_ref; TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;

/* Variables and functions */
 int /*<<< orphan*/  nfs41_open_stateid_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int write_to_mds (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int write_to_pnfs (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_write(nfs41_upcall *upcall)
{
    readwrite_upcall_args *args = &upcall->args.rw;
    stateid_arg stateid;
    uint32_t pnfs_bytes_written = 0;
    int status;

    nfs41_open_stateid_arg(upcall->state_ref, &stateid);

#ifdef PNFS_ENABLE_WRITE
    status = write_to_pnfs(upcall, &stateid);
    if (args->out_len) {
        pnfs_bytes_written = args->out_len;
        args->out_len = 0;

        args->offset += pnfs_bytes_written;
        args->buffer += pnfs_bytes_written;
        args->len -= pnfs_bytes_written;

        if (args->len == 0)
            goto out;
    }
#endif

    status = write_to_mds(upcall, &stateid);
out:
    args->out_len += pnfs_bytes_written;
    return status;
}