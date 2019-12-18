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
struct d3d8_handle_table {size_t entry_count; struct d3d8_handle_entry* entries; } ;
struct d3d8_handle_entry {int type; void* object; } ;
typedef  enum d3d8_handle_type { ____Placeholder_d3d8_handle_type } d3d8_handle_type ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t D3D8_INVALID_HANDLE ; 
 int /*<<< orphan*/  WARN (char*,size_t,...) ; 

__attribute__((used)) static void *d3d8_get_object(struct d3d8_handle_table *t, DWORD handle, enum d3d8_handle_type type)
{
    struct d3d8_handle_entry *entry;

    if (handle == D3D8_INVALID_HANDLE || handle >= t->entry_count)
    {
        WARN("Invalid handle %u passed.\n", handle);
        return NULL;
    }

    entry = &t->entries[handle];
    if (entry->type != type)
    {
        WARN("Handle %u(%p) is not of type %#x.\n", handle, entry, type);
        return NULL;
    }

    return entry->object;
}