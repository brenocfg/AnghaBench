#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_gl_info {int dummy; } ;
struct shader_glsl_priv {int /*<<< orphan*/  program_lookup; } ;
struct TYPE_12__ {int /*<<< orphan*/  shader_entry; scalar_t__ id; } ;
struct TYPE_11__ {int /*<<< orphan*/  shader_entry; scalar_t__ id; } ;
struct TYPE_10__ {int /*<<< orphan*/  shader_entry; scalar_t__ id; } ;
struct TYPE_9__ {int /*<<< orphan*/  shader_entry; scalar_t__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  shader_entry; scalar_t__ id; } ;
struct TYPE_7__ {int /*<<< orphan*/  shader_entry; scalar_t__ id; } ;
struct glsl_shader_prog_link {TYPE_6__ cs; TYPE_5__ ps; TYPE_4__ gs; TYPE_3__ ds; TYPE_2__ hs; TYPE_1__ vs; int /*<<< orphan*/  id; int /*<<< orphan*/  program_lookup_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (struct glsl_shader_prog_link*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_rb_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_glsl_program_entry(struct shader_glsl_priv *priv, const struct wined3d_gl_info *gl_info,
        struct glsl_shader_prog_link *entry)
{
    wine_rb_remove(&priv->program_lookup, &entry->program_lookup_entry);

    GL_EXTCALL(glDeleteProgram(entry->id));
    if (entry->vs.id)
        list_remove(&entry->vs.shader_entry);
    if (entry->hs.id)
        list_remove(&entry->hs.shader_entry);
    if (entry->ds.id)
        list_remove(&entry->ds.shader_entry);
    if (entry->gs.id)
        list_remove(&entry->gs.shader_entry);
    if (entry->ps.id)
        list_remove(&entry->ps.shader_entry);
    if (entry->cs.id)
        list_remove(&entry->cs.shader_entry);
    heap_free(entry);
}