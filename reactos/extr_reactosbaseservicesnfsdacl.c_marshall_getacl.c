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
struct TYPE_7__ {int sec_desc_len; int* sec_desc; } ;
struct TYPE_5__ {TYPE_3__ getacl; } ;
struct TYPE_6__ {TYPE_1__ args; } ;
typedef  TYPE_2__ nfs41_upcall ;
typedef  TYPE_3__ getacl_upcall_args ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  free (int*) ; 
 int safe_write (unsigned char**,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int marshall_getacl(unsigned char *buffer, uint32_t *length, 
                           nfs41_upcall *upcall)
{
    int status = ERROR_NOT_SUPPORTED;
    getacl_upcall_args *args = &upcall->args.getacl;

    status = safe_write(&buffer, length, &args->sec_desc_len, sizeof(DWORD));
    if (status) goto out;
    status = safe_write(&buffer, length, args->sec_desc, args->sec_desc_len);
    free(args->sec_desc);
    if (status) goto out;
out:
    return status;
}