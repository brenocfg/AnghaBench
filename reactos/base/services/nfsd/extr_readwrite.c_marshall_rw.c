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
struct TYPE_6__ {int /*<<< orphan*/  ctime; int /*<<< orphan*/  out_len; } ;
typedef  TYPE_2__ readwrite_upcall_args ;
struct TYPE_5__ {TYPE_2__ rw; } ;
struct TYPE_7__ {TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;

/* Variables and functions */
 int safe_write (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int marshall_rw(unsigned char *buffer, uint32_t *length, nfs41_upcall *upcall)
{
    readwrite_upcall_args *args = &upcall->args.rw;
    int status;
    status = safe_write(&buffer, length, &args->out_len, sizeof(args->out_len));
    if (status) goto out;
    status = safe_write(&buffer, length, &args->ctime, sizeof(args->ctime));
out:
    return status;
}