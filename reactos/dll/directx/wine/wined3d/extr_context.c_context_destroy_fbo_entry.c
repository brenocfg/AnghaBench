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
struct wined3d_context {int /*<<< orphan*/  fbo_entry_count; } ;
struct fbo_entry {int /*<<< orphan*/  entry; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  context_destroy_fbo (struct wined3d_context*,scalar_t__) ; 
 int /*<<< orphan*/  heap_free (struct fbo_entry*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void context_destroy_fbo_entry(struct wined3d_context *context, struct fbo_entry *entry)
{
    if (entry->id)
    {
        TRACE("Destroy FBO %u.\n", entry->id);
        context_destroy_fbo(context, entry->id);
    }
    --context->fbo_entry_count;
    list_remove(&entry->entry);
    heap_free(entry);
}