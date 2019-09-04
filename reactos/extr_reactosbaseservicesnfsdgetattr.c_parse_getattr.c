#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  query_class; } ;
struct TYPE_9__ {TYPE_5__ getattr; } ;
struct TYPE_10__ {TYPE_2__* state_ref; TYPE_3__ args; } ;
typedef  TYPE_4__ nfs41_upcall ;
typedef  TYPE_5__ getattr_upcall_args ;
struct TYPE_7__ {int /*<<< orphan*/  path; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_1__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int safe_read (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_getattr(unsigned char *buffer, uint32_t length, nfs41_upcall *upcall)
{
    int status;
    getattr_upcall_args *args = &upcall->args.getattr;

    status = safe_read(&buffer, &length, &args->query_class, sizeof(args->query_class));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->buf_len, sizeof(args->buf_len));
    if (status) goto out;

    dprintf(1, "parsing NFS41_FILE_QUERY: info_class=%d buf_len=%d file=%.*s\n",
        args->query_class, args->buf_len, upcall->state_ref->path.len, 
        upcall->state_ref->path.path);
out:
    return status;
}