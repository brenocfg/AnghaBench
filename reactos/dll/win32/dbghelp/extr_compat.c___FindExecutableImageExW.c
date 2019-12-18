#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PFIND_EXE_FILE_CALLBACKW ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

HANDLE __FindExecutableImageExW(PCWSTR file, PCWSTR path, PWSTR out_buffer, PFIND_EXE_FILE_CALLBACKW x, PVOID y)
{
    HANDLE ret = CreateFileW(file, 0, 0, NULL, 0, 0, NULL);
    if(ret)
        memcpy(out_buffer, file, (strlenW(file) + 1)*sizeof(WCHAR));

    return ret;
}