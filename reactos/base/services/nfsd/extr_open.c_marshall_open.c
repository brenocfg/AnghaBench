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
struct TYPE_7__ {int len; int /*<<< orphan*/  path; } ;
struct TYPE_8__ {unsigned short basic_info; unsigned short std_info; unsigned short mode; unsigned short changeattr; unsigned short deleg_type; unsigned short symlink_embedded; TYPE_2__ symlink; } ;
typedef  TYPE_3__ open_upcall_args ;
struct TYPE_6__ {TYPE_3__ open; } ;
struct TYPE_9__ {unsigned short state_ref; scalar_t__ last_error; TYPE_1__ args; } ;
typedef  TYPE_4__ nfs41_upcall ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int ERROR_BUFFER_OVERFLOW ; 
 scalar_t__ ERROR_REPARSE ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  dprintf (int,char*,unsigned short,unsigned short,unsigned short) ; 
 int safe_write (unsigned char**,unsigned short*,unsigned short*,int) ; 

__attribute__((used)) static int marshall_open(unsigned char *buffer, uint32_t *length, nfs41_upcall *upcall)
{
    int status;
    open_upcall_args *args = &upcall->args.open;

    status = safe_write(&buffer, length, &args->basic_info, sizeof(args->basic_info));
    if (status) goto out;
    status = safe_write(&buffer, length, &args->std_info, sizeof(args->std_info));
    if (status) goto out;
    status = safe_write(&buffer, length, &upcall->state_ref, sizeof(HANDLE));
    if (status) goto out;
    status = safe_write(&buffer, length, &args->mode, sizeof(args->mode));
    if (status) goto out;
    status = safe_write(&buffer, length, &args->changeattr, sizeof(args->changeattr));
    if (status) goto out;
    status = safe_write(&buffer, length, &args->deleg_type, sizeof(args->deleg_type));
    if (status) goto out;
    if (upcall->last_error == ERROR_REPARSE) {
        unsigned short len = (args->symlink.len + 1) * sizeof(WCHAR);
        status = safe_write(&buffer, length, &args->symlink_embedded, sizeof(BOOLEAN));
        if (status) goto out;
        status = safe_write(&buffer, length, &len, sizeof(len));
        if (status) goto out;
        /* convert args->symlink to wchar */
        if (*length <= len || !MultiByteToWideChar(CP_UTF8, 0,
            args->symlink.path, args->symlink.len,
            (LPWSTR)buffer, len / sizeof(WCHAR))) {
            status = ERROR_BUFFER_OVERFLOW;
            goto out;
        }
    }
    dprintf(2, "NFS41_OPEN: downcall open_state=0x%p mode %o changeattr 0x%llu\n", 
        upcall->state_ref, args->mode, args->changeattr);
out:
    return status;
}