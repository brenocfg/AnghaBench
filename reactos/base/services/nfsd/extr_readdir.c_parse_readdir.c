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
struct TYPE_6__ {int /*<<< orphan*/  kbuf; int /*<<< orphan*/  single; int /*<<< orphan*/  restart; int /*<<< orphan*/  initial; int /*<<< orphan*/  filter; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  query_class; int /*<<< orphan*/  state; int /*<<< orphan*/  root; } ;
typedef  TYPE_2__ readdir_upcall_args ;
struct TYPE_5__ {TYPE_2__ readdir; } ;
struct TYPE_7__ {int /*<<< orphan*/  state_ref; int /*<<< orphan*/  root_ref; TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_name (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int safe_read (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_readdir(unsigned char *buffer, uint32_t length, nfs41_upcall *upcall)
{
    int status;
    readdir_upcall_args *args = &upcall->args.readdir;

    status = safe_read(&buffer, &length, &args->query_class, sizeof(args->query_class));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->buf_len, sizeof(args->buf_len));
    if (status) goto out;
    status = get_name(&buffer, &length, &args->filter);
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->initial, sizeof(args->initial));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->restart, sizeof(args->restart));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->single, sizeof(args->single));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->kbuf, sizeof(args->kbuf));
    if (status) goto out;
    args->root = upcall->root_ref;
    args->state = upcall->state_ref;

    dprintf(1, "parsing NFS41_DIR_QUERY: info_class=%d buf_len=%d "
        "filter='%s'\n\tInitial\\Restart\\Single %d\\%d\\%d buf=%p\n",
        args->query_class, args->buf_len, args->filter,
        args->initial, args->restart, args->single, args->kbuf);
out:
    return status;
}