#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  urlcache_header ;
struct TYPE_4__ {scalar_t__ mapping; int /*<<< orphan*/  mutex; int /*<<< orphan*/  path; scalar_t__ file_size; } ;
typedef  TYPE_1__ cache_container ;
typedef  char WCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateDirectoryW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFileW (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FILE_MAP_WRITE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 scalar_t__ FILE_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  FreeUrlCacheSpaceW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ INVALID_FILE_SIZE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ MAX_BLOCK_NO ; 
 int MAX_PATH ; 
 scalar_t__ MIN_BLOCK_NO ; 
 int /*<<< orphan*/ * MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_ALWAYS ; 
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_container_is_valid (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ cache_container_map_index (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 scalar_t__ cache_container_set_size (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  strcpyW (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD cache_container_open_index(cache_container *container, DWORD blocks_no)
{
    static const WCHAR index_dat[] = {'i','n','d','e','x','.','d','a','t',0};

    HANDLE file;
    WCHAR index_path[MAX_PATH];
    DWORD file_size;
    BOOL validate;

    WaitForSingleObject(container->mutex, INFINITE);

    if(container->mapping) {
        ReleaseMutex(container->mutex);
        return ERROR_SUCCESS;
    }

    strcpyW(index_path, container->path);
    strcatW(index_path, index_dat);

    file = CreateFileW(index_path, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
    if(file == INVALID_HANDLE_VALUE) {
	/* Maybe the directory wasn't there? Try to create it */
	if(CreateDirectoryW(container->path, 0))
            file = CreateFileW(index_path, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
    }
    if(file == INVALID_HANDLE_VALUE) {
        TRACE("Could not open or create cache index file \"%s\"\n", debugstr_w(index_path));
        ReleaseMutex(container->mutex);
        return GetLastError();
    }

    file_size = GetFileSize(file, NULL);
    if(file_size == INVALID_FILE_SIZE) {
        CloseHandle(file);
	ReleaseMutex(container->mutex);
        return GetLastError();
    }

    if(blocks_no < MIN_BLOCK_NO)
        blocks_no = MIN_BLOCK_NO;
    else if(blocks_no > MAX_BLOCK_NO)
        blocks_no = MAX_BLOCK_NO;

    if(file_size < FILE_SIZE(blocks_no)) {
        DWORD ret = cache_container_set_size(container, file, blocks_no);
        CloseHandle(file);
        ReleaseMutex(container->mutex);
        return ret;
    }

    container->file_size = file_size;
    container->mapping = cache_container_map_index(file, container->path, file_size, &validate);
    CloseHandle(file);
    if(container->mapping && validate) {
        urlcache_header *header = MapViewOfFile(container->mapping, FILE_MAP_WRITE, 0, 0, 0);

        if(header && !cache_container_is_valid(header, file_size)) {
            WARN("detected old or broken index.dat file\n");
            UnmapViewOfFile(header);
            FreeUrlCacheSpaceW(container->path, 100, 0);
        }else if(header) {
            UnmapViewOfFile(header);
        }else {
            CloseHandle(container->mapping);
            container->mapping = NULL;
        }
    }

    if(!container->mapping)
    {
        ERR("Couldn't create file mapping (error is %d)\n", GetLastError());
        ReleaseMutex(container->mutex);
        return GetLastError();
    }

    ReleaseMutex(container->mutex);
    return ERROR_SUCCESS;
}