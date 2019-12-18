#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct _finddata_t {scalar_t__ attrib; int /*<<< orphan*/  name; int /*<<< orphan*/  size; void* time_write; void* time_access; void* time_create; } ;
struct TYPE_3__ {scalar_t__ dwFileAttributes; int /*<<< orphan*/  cFileName; int /*<<< orphan*/  nFileSizeLow; int /*<<< orphan*/  ftLastWriteTime; int /*<<< orphan*/  ftLastAccessTime; int /*<<< orphan*/  ftCreationTime; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
#define  ERROR_FILE_NOT_FOUND 131 
#define  ERROR_NOT_ENOUGH_MEMORY 130 
#define  ERROR_NO_MORE_FILES 129 
#define  ERROR_PATH_NOT_FOUND 128 
 scalar_t__ FILE_ATTRIBUTE_NORMAL ; 
 scalar_t__ FindFirstFile (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  mbstowcs (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 void* wceex_filetime_to_time (int /*<<< orphan*/ *) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcstombs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

intptr_t wceex_findfirst(const char *filespec, struct _finddata_t *fileinfo)
{
    WIN32_FIND_DATA wfd;
    HANDLE          hFile;
    DWORD           err;
    wchar_t         wfilename[MAX_PATH];
    
    mbstowcs(wfilename, filespec, strlen(filespec) + 1);
    
    /* XXX - mloskot - set errno values! */
    
    hFile = FindFirstFile(wfilename, &wfd);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        err = GetLastError();
        switch (err)
        {
        case ERROR_NO_MORE_FILES:
        case ERROR_FILE_NOT_FOUND:
        case ERROR_PATH_NOT_FOUND:
            //errno = ENOENT;
            break;
            
        case ERROR_NOT_ENOUGH_MEMORY:
            //errno = ENOMEM;
            break;
            
        default:
            //errno = EINVAL;
            break;
        }
        return (-1);
    }
    
    fileinfo->attrib = (wfd.dwFileAttributes == FILE_ATTRIBUTE_NORMAL) ? 0 : wfd.dwFileAttributes;
    fileinfo->time_create  = wceex_filetime_to_time(&wfd.ftCreationTime);
    fileinfo->time_access  = wceex_filetime_to_time(&wfd.ftLastAccessTime);
    fileinfo->time_write   = wceex_filetime_to_time(&wfd.ftLastWriteTime);
    
    fileinfo->size = wfd.nFileSizeLow;
    wcstombs(fileinfo->name, wfd.cFileName, wcslen(wfd.cFileName) + 1);
    
    return (intptr_t)hFile;
}