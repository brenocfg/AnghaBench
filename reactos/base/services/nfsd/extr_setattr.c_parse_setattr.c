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
struct TYPE_6__ {unsigned char* buf; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  set_class; int /*<<< orphan*/  path; int /*<<< orphan*/  state; int /*<<< orphan*/  root; } ;
typedef  TYPE_2__ setattr_upcall_args ;
struct TYPE_5__ {TYPE_2__ setattr; } ;
struct TYPE_7__ {int /*<<< orphan*/  state_ref; int /*<<< orphan*/  root_ref; TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_name (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int safe_read (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_setattr(unsigned char *buffer, uint32_t length, nfs41_upcall *upcall)
{
    int status;
    setattr_upcall_args *args = &upcall->args.setattr;

    status = get_name(&buffer, &length, &args->path);
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->set_class, sizeof(args->set_class));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->buf_len, sizeof(args->buf_len));
    if (status) goto out;

    args->buf = buffer;
    args->root = upcall->root_ref;
    args->state = upcall->state_ref;

    dprintf(1, "parsing NFS41_FILE_SET: filename='%s' info_class=%d "
        "buf_len=%d\n", args->path, args->set_class, args->buf_len);
out:
    return status;
}