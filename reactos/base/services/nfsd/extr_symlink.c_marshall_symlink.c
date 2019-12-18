#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned short uint32_t ;
struct TYPE_6__ {int len; int /*<<< orphan*/  path; } ;
struct TYPE_8__ {TYPE_1__ target_get; scalar_t__ set; } ;
typedef  TYPE_3__ symlink_upcall_args ;
struct TYPE_7__ {TYPE_3__ symlink; } ;
struct TYPE_9__ {TYPE_2__ args; } ;
typedef  TYPE_4__ nfs41_upcall ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int ERROR_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned short) ; 
 int NO_ERROR ; 
 int safe_write (unsigned char**,unsigned short*,unsigned short*,int) ; 

__attribute__((used)) static int marshall_symlink(unsigned char *buffer, uint32_t *length, nfs41_upcall *upcall)
{
    symlink_upcall_args *args = &upcall->args.symlink;
    unsigned short len = (args->target_get.len + 1) * sizeof(WCHAR);
    int status = NO_ERROR;

    if (args->set)
        goto out;

    status = safe_write(&buffer, length, &len, sizeof(len));
    if (status) goto out;

    if (*length <= len || !MultiByteToWideChar(CP_UTF8, 0,
            args->target_get.path, args->target_get.len,
            (LPWSTR)buffer, len / sizeof(WCHAR))) {
        status = ERROR_BUFFER_OVERFLOW;
        goto out;
    }
out:
    return status;
}