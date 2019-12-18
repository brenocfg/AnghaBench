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
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CREATE_NEW ; 
 scalar_t__ ERROR_FILE_EXISTS ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FormatMessageW (int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRING_CANCELLED ; 
 int /*<<< orphan*/  STRING_OVERWRITE_FILE ; 
 int /*<<< orphan*/  ask_confirm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_writeconsole (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HANDLE get_file_handle(WCHAR *filename, BOOL overwrite_file)
{
    HANDLE hFile = create_file(filename, overwrite_file ? CREATE_ALWAYS : CREATE_NEW);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        DWORD error = GetLastError();

        if (error == ERROR_FILE_EXISTS)
        {
            if (!ask_confirm(STRING_OVERWRITE_FILE, filename))
            {
                output_message(STRING_CANCELLED);
                exit(0);
            }

            hFile = create_file(filename, CREATE_ALWAYS);
        }
        else
        {
            WCHAR *str;

            FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                           FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, 0, (WCHAR *)&str, 0, NULL);
            output_writeconsole(str, lstrlenW(str));
            LocalFree(str);
            exit(1);
        }
    }

    return hFile;
}