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
struct TYPE_7__ {int /*<<< orphan*/  query; } ;
struct TYPE_5__ {TYPE_3__ getacl; } ;
struct TYPE_6__ {TYPE_1__ args; } ;
typedef  TYPE_2__ nfs41_upcall ;
typedef  TYPE_3__ getacl_upcall_args ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ) ; 
 int safe_read (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_getacl(unsigned char *buffer, uint32_t length, 
                        nfs41_upcall *upcall)
{
    int status;
    getacl_upcall_args *args = &upcall->args.getacl;

    status = safe_read(&buffer, &length, &args->query, sizeof(args->query));
    if (status) goto out;

    dprintf(1, "parsing NFS41_ACL_QUERY: info_class=%d\n", args->query);
out:
    return status;
}