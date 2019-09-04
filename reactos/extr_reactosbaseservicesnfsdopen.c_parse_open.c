#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  path; } ;
struct TYPE_7__ {int /*<<< orphan*/  create_opts; int /*<<< orphan*/  access_mode; int /*<<< orphan*/  access_mask; int /*<<< orphan*/  disposition; int /*<<< orphan*/  ea; TYPE_5__ symlink; int /*<<< orphan*/  srv_open; int /*<<< orphan*/  mode; int /*<<< orphan*/  open_owner_id; int /*<<< orphan*/  file_attrs; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ open_upcall_args ;
struct TYPE_6__ {TYPE_2__ open; } ;
struct TYPE_8__ {TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_name (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parse_abs_path (unsigned char**,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  print_access_mask (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_create_attributes (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_disposition (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_share_mode (int,int /*<<< orphan*/ ) ; 
 int safe_read (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_open(unsigned char *buffer, uint32_t length, nfs41_upcall *upcall)
{
    int status;
    open_upcall_args *args = &upcall->args.open;

    status = get_name(&buffer, &length, &args->path);
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->access_mask, sizeof(ULONG));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->access_mode, sizeof(ULONG));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->file_attrs, sizeof(ULONG));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->create_opts, sizeof(ULONG));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->disposition, sizeof(ULONG));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->open_owner_id, sizeof(LONG));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->mode, sizeof(DWORD));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->srv_open, sizeof(HANDLE));
    if (status) goto out;
    status = parse_abs_path(&buffer, &length, &args->symlink);
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->ea, sizeof(HANDLE));
    if (status) goto out;

    dprintf(1, "parsing NFS41_OPEN: filename='%s' access mask=%d "
        "access mode=%d\n\tfile attrs=0x%x create attrs=0x%x "
        "(kernel) disposition=%d\n\topen_owner_id=%d mode=%o "
        "srv_open=%p symlink=%s ea=%p\n", args->path, args->access_mask,
        args->access_mode, args->file_attrs, args->create_opts,
        args->disposition, args->open_owner_id, args->mode, args->srv_open,
        args->symlink.path, args->ea);
    print_disposition(2, args->disposition);
    print_access_mask(2, args->access_mask);
    print_share_mode(2, args->access_mode);
    print_create_attributes(2, args->create_opts);
out:
    return status;
}