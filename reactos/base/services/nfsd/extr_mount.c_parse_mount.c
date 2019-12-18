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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  wsize; int /*<<< orphan*/  rsize; int /*<<< orphan*/  sec_flavor; int /*<<< orphan*/  path; int /*<<< orphan*/  hostname; } ;
struct TYPE_5__ {TYPE_3__ mount; } ;
struct TYPE_6__ {TYPE_1__ args; } ;
typedef  TYPE_2__ nfs41_upcall ;
typedef  TYPE_3__ mount_upcall_args ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_name (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int safe_read (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secflavorop2name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_mount(unsigned char *buffer, uint32_t length, nfs41_upcall *upcall) 
{
    int status;
    mount_upcall_args *args = &upcall->args.mount;

    status = get_name(&buffer, &length, &args->hostname);
    if(status) goto out;
    status = get_name(&buffer, &length, &args->path);
    if(status) goto out;
    status = safe_read(&buffer, &length, &args->sec_flavor, sizeof(DWORD));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->rsize, sizeof(DWORD));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->wsize, sizeof(DWORD));
    if (status) goto out;

    dprintf(1, "parsing NFS14_MOUNT: srv_name=%s root=%s sec_flavor=%s "
        "rsize=%d wsize=%d\n", args->hostname, args->path, 
        secflavorop2name(args->sec_flavor), args->rsize, args->wsize);
out:
    return status;
}