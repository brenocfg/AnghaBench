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
struct TYPE_7__ {unsigned char* ealist; scalar_t__ single; scalar_t__ restart; scalar_t__ eaindex; scalar_t__ buf_len; scalar_t__ ealist_len; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {TYPE_3__ getexattr; } ;
struct TYPE_6__ {TYPE_1__ args; } ;
typedef  TYPE_2__ nfs41_upcall ;
typedef  TYPE_3__ getexattr_upcall_args ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (int,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int get_name (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int safe_read (unsigned char**,int /*<<< orphan*/ *,scalar_t__*,int) ; 

__attribute__((used)) static int parse_getexattr(unsigned char *buffer, uint32_t length, nfs41_upcall *upcall)
{
    int status;
    getexattr_upcall_args *args = &upcall->args.getexattr;

    status = get_name(&buffer, &length, &args->path);
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->eaindex, sizeof(args->eaindex));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->restart, sizeof(args->restart));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->single, sizeof(args->single));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->buf_len, sizeof(args->buf_len));
    if (status) goto out;
    status = safe_read(&buffer, &length, &args->ealist_len, sizeof(args->ealist_len));
    if (status) goto out;
    args->ealist = args->ealist_len ? buffer : NULL;

    dprintf(1, "parsing NFS41_EA_GET: buf_len=%d Index %d Restart %d "
        "Single %d\n", args->buf_len,args->eaindex, args->restart, args->single);
out:
    return status;
}