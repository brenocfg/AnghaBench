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
struct TYPE_6__ {unsigned char* buf; int /*<<< orphan*/  count; int /*<<< orphan*/  buf_len; } ;
typedef  TYPE_2__ unlock_upcall_args ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_2__ unlock; } ;
struct TYPE_7__ {TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ) ; 
 int safe_read (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_unlock(unsigned char *buffer, uint32_t length, nfs41_upcall *upcall)
{
    int status;
    unlock_upcall_args *args = &upcall->args.unlock;

    status = safe_read(&buffer, &length, &args->count, sizeof(ULONG));
    if (status) goto out;

    args->buf = buffer;
    args->buf_len = length;

    dprintf(1, "parsing NFS41_UNLOCK: count=%u\n", args->count);
out:
    return status;
}