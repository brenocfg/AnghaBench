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
typedef  int /*<<< orphan*/  object_header_t ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_SUCCESS ; 
 int INET_QueryOption (int /*<<< orphan*/ *,int,void*,int*,int /*<<< orphan*/ ) ; 
 int INTERNET_HANDLE_TYPE_FTP_FIND ; 
#define  INTERNET_OPTION_HANDLE_TYPE 128 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static DWORD FTPFINDNEXT_QueryOption(object_header_t *hdr, DWORD option, void *buffer, DWORD *size, BOOL unicode)
{
    switch(option) {
    case INTERNET_OPTION_HANDLE_TYPE:
        TRACE("INTERNET_OPTION_HANDLE_TYPE\n");

        if (*size < sizeof(ULONG))
            return ERROR_INSUFFICIENT_BUFFER;

        *size = sizeof(DWORD);
        *(DWORD*)buffer = INTERNET_HANDLE_TYPE_FTP_FIND;
        return ERROR_SUCCESS;
    }

    return INET_QueryOption(hdr, option, buffer, size, unicode);
}