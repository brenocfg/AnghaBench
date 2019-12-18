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
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  char* LPSTR ;
typedef  int* LPLONG ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int LONG ;
typedef  size_t BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t CACHE_CONTAINER_NO_SUBDIR ; 
 int /*<<< orphan*/  CP_ACP ; 
 int DIR_LENGTH ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL urlcache_create_file_pathA(
    const cache_container *pContainer,
    const urlcache_header *pHeader,
    LPCSTR szLocalFileName,
    BYTE Directory,
    LPSTR szPath,
    LPLONG lpBufferSize)
{
    LONG nRequired;
    int path_len, file_name_len, dir_len;

    if (Directory!=CACHE_CONTAINER_NO_SUBDIR && Directory>=pHeader->dirs_no)
    {
        *lpBufferSize = 0;
        return FALSE;
    }

    path_len = WideCharToMultiByte(CP_ACP, 0, pContainer->path, -1, NULL, 0, NULL, NULL) - 1;
    file_name_len = strlen(szLocalFileName) + 1 /* for nul-terminator */;
    if (Directory!=CACHE_CONTAINER_NO_SUBDIR)
        dir_len = DIR_LENGTH+1;
    else
        dir_len = 0;

    nRequired = (path_len + dir_len + file_name_len) * sizeof(char);
    if (nRequired <= *lpBufferSize)
    {
        WideCharToMultiByte(CP_ACP, 0, pContainer->path, -1, szPath, path_len, NULL, NULL);
        if(dir_len) {
            memcpy(szPath+path_len, pHeader->directory_data[Directory].name, dir_len-1);
            szPath[path_len + dir_len-1] = '\\';
        }
        memcpy(szPath + path_len + dir_len, szLocalFileName, file_name_len);
        *lpBufferSize = nRequired;
        return TRUE;
    }
    *lpBufferSize = nRequired;
    return FALSE;
}