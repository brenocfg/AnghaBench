#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* options; } ;
typedef  TYPE_1__ urlcache_header ;
struct TYPE_8__ {scalar_t__ exempt_delta; int /*<<< orphan*/  header; } ;
typedef  TYPE_2__ entry_url ;
typedef  int /*<<< orphan*/  cache_container ;
typedef  scalar_t__ LPBYTE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t CACHE_HEADER_DATA_ROOT_LEAK_OFFSET ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  urlcache_delete_file (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  urlcache_entry_free (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL urlcache_clean_leaked_entries(cache_container *container, urlcache_header *header)
{
    DWORD *leak_off;
    BOOL freed = FALSE;

    leak_off = &header->options[CACHE_HEADER_DATA_ROOT_LEAK_OFFSET];
    while(*leak_off) {
        entry_url *url_entry = (entry_url*)((LPBYTE)header + *leak_off);

        if(SUCCEEDED(urlcache_delete_file(container, header, url_entry))) {
            *leak_off = url_entry->exempt_delta;
            urlcache_entry_free(header, &url_entry->header);
            freed = TRUE;
        }else {
            leak_off = &url_entry->exempt_delta;
        }
    }

    return freed;
}