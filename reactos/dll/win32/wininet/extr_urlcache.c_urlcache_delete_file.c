#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ QuadPart; } ;
struct TYPE_13__ {scalar_t__ QuadPart; } ;
struct TYPE_16__ {size_t dirs_no; TYPE_4__ cache_usage; TYPE_2__ exempt_usage; TYPE_1__* directory_data; } ;
typedef  TYPE_5__ urlcache_header ;
typedef  int /*<<< orphan*/  path ;
struct TYPE_14__ {scalar_t__ QuadPart; } ;
struct TYPE_17__ {size_t cache_dir; scalar_t__ write_date; scalar_t__ write_time; int cache_entry_type; TYPE_3__ size; scalar_t__ local_name_off; } ;
typedef  TYPE_6__ entry_url ;
typedef  int /*<<< orphan*/  cache_container ;
typedef  scalar_t__ WORD ;
struct TYPE_18__ {int /*<<< orphan*/  ftLastWriteTime; } ;
typedef  TYPE_7__ WIN32_FILE_ATTRIBUTE_DATA ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {scalar_t__ files_no; } ;
typedef  scalar_t__ LPCSTR ;
typedef  int LONG ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DeleteFileW (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_SHARING_VIOLATION ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetFileAttributesExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  GetFileExInfoStandard ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int STICKY_CACHE_ENTRY ; 
 int /*<<< orphan*/  file_time_to_dos_date_time (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  urlcache_create_file_pathW (int /*<<< orphan*/  const*,TYPE_5__*,scalar_t__,size_t,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD urlcache_delete_file(const cache_container *container,
        urlcache_header *header, entry_url *url_entry)
{
    WIN32_FILE_ATTRIBUTE_DATA attr;
    WCHAR path[MAX_PATH];
    LONG path_size = sizeof(path);
    DWORD err;
    WORD date, time;

    if(!url_entry->local_name_off)
        goto succ;

    if(!urlcache_create_file_pathW(container, header,
                (LPCSTR)url_entry+url_entry->local_name_off,
                url_entry->cache_dir, path, &path_size, FALSE))
        goto succ;

    if(!GetFileAttributesExW(path, GetFileExInfoStandard, &attr))
        goto succ;
    file_time_to_dos_date_time(&attr.ftLastWriteTime, &date, &time);
    if(date != url_entry->write_date || time != url_entry->write_time)
        goto succ;

    err = (DeleteFileW(path) ? ERROR_SUCCESS : GetLastError());
    if(err == ERROR_ACCESS_DENIED || err == ERROR_SHARING_VIOLATION)
        return err;

succ:
    if (url_entry->cache_dir < header->dirs_no)
    {
        if (header->directory_data[url_entry->cache_dir].files_no)
            header->directory_data[url_entry->cache_dir].files_no--;
    }
    if (url_entry->cache_entry_type & STICKY_CACHE_ENTRY)
    {
        if (url_entry->size.QuadPart < header->exempt_usage.QuadPart)
            header->exempt_usage.QuadPart -= url_entry->size.QuadPart;
        else
            header->exempt_usage.QuadPart = 0;
    }
    else
    {
        if (url_entry->size.QuadPart < header->cache_usage.QuadPart)
            header->cache_usage.QuadPart -= url_entry->size.QuadPart;
        else
            header->cache_usage.QuadPart = 0;
    }

    return ERROR_SUCCESS;
}