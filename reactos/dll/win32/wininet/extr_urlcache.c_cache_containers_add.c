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
struct TYPE_4__ {int /*<<< orphan*/  entry; struct TYPE_4__* path; int /*<<< orphan*/ * mutex; void* cache_prefix; int /*<<< orphan*/  default_entry_type; scalar_t__ file_size; int /*<<< orphan*/ * mapping; } ;
typedef  TYPE_1__ cache_container ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CharLowerW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateMutexW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UrlContainers ; 
 int /*<<< orphan*/  cache_container_create_object_name (int /*<<< orphan*/ ,char) ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 TYPE_1__* heap_strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static BOOL cache_containers_add(const char *cache_prefix, LPCWSTR path,
        DWORD default_entry_type, LPWSTR mutex_name)
{
    cache_container *pContainer = heap_alloc(sizeof(cache_container));
    int cache_prefix_len = strlen(cache_prefix);

    if (!pContainer)
    {
        return FALSE;
    }

    pContainer->mapping = NULL;
    pContainer->file_size = 0;
    pContainer->default_entry_type = default_entry_type;

    pContainer->path = heap_strdupW(path);
    if (!pContainer->path)
    {
        heap_free(pContainer);
        return FALSE;
    }

    pContainer->cache_prefix = heap_alloc(cache_prefix_len+1);
    if (!pContainer->cache_prefix)
    {
        heap_free(pContainer->path);
        heap_free(pContainer);
        return FALSE;
    }

    memcpy(pContainer->cache_prefix, cache_prefix, cache_prefix_len+1);

    CharLowerW(mutex_name);
    cache_container_create_object_name(mutex_name, '!');

    if ((pContainer->mutex = CreateMutexW(NULL, FALSE, mutex_name)) == NULL)
    {
        ERR("couldn't create mutex (error is %d)\n", GetLastError());
        heap_free(pContainer->path);
        heap_free(pContainer);
        return FALSE;
    }

    list_add_head(&UrlContainers, &pContainer->entry);

    return TRUE;
}