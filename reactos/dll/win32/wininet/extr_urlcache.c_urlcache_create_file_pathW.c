#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t dirs_no; TYPE_1__* directory_data; } ;
typedef  TYPE_2__ urlcache_header ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ cache_container ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  char* LPWSTR ;
typedef  int* LPLONG ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int LONG ;
typedef  size_t BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t CACHE_CONTAINER_NO_SUBDIR ; 
 int /*<<< orphan*/  CP_ACP ; 
 int DIR_LENGTH ; 
 scalar_t__ FALSE ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL urlcache_create_file_pathW(
    const cache_container *pContainer,
    const urlcache_header *pHeader,
    LPCSTR szLocalFileName,
    BYTE Directory,
    LPWSTR wszPath,
    LPLONG lpBufferSize,
    BOOL trunc_name)
{
    LONG nRequired;
    int path_len = strlenW(pContainer->path);
    int file_name_len = MultiByteToWideChar(CP_ACP, 0, szLocalFileName, -1, NULL, 0);
    if (Directory!=CACHE_CONTAINER_NO_SUBDIR && Directory>=pHeader->dirs_no)
    {
        *lpBufferSize = 0;
        return FALSE;
    }

    nRequired = (path_len + file_name_len) * sizeof(WCHAR);
    if(Directory != CACHE_CONTAINER_NO_SUBDIR)
        nRequired += (DIR_LENGTH + 1) * sizeof(WCHAR);
    if (trunc_name && nRequired >= *lpBufferSize)
        nRequired = *lpBufferSize;
    if (nRequired <= *lpBufferSize)
    {
        int dir_len;

        memcpy(wszPath, pContainer->path, path_len * sizeof(WCHAR));
        if (Directory != CACHE_CONTAINER_NO_SUBDIR)
        {
            dir_len = MultiByteToWideChar(CP_ACP, 0, pHeader->directory_data[Directory].name, DIR_LENGTH, wszPath + path_len, DIR_LENGTH);
            wszPath[dir_len + path_len] = '\\';
            dir_len++;
        }
        else
        {
            dir_len = 0;
        }
        MultiByteToWideChar(CP_ACP, 0, szLocalFileName, -1, wszPath + dir_len + path_len,
                *lpBufferSize/sizeof(WCHAR)-dir_len-path_len);
        wszPath[*lpBufferSize/sizeof(WCHAR)-1] = 0;
        *lpBufferSize = nRequired;
        return TRUE;
    }
    *lpBufferSize = nRequired;
    return FALSE;
}