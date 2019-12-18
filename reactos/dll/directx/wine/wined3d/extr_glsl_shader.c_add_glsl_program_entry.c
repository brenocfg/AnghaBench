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
struct shader_glsl_priv {int /*<<< orphan*/  program_lookup; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct glsl_shader_prog_link {int /*<<< orphan*/  program_lookup_entry; TYPE_5__ cs; TYPE_4__ ps; TYPE_3__ gs; TYPE_2__ ds; TYPE_1__ hs; TYPE_6__ vs; } ;
struct glsl_program_key {int /*<<< orphan*/  cs_id; int /*<<< orphan*/  ps_id; int /*<<< orphan*/  gs_id; int /*<<< orphan*/  ds_id; int /*<<< orphan*/  hs_id; int /*<<< orphan*/  vs_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int wine_rb_put (int /*<<< orphan*/ *,struct glsl_program_key*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_glsl_program_entry(struct shader_glsl_priv *priv, struct glsl_shader_prog_link *entry)
{
    struct glsl_program_key key;

    key.vs_id = entry->vs.id;
    key.hs_id = entry->hs.id;
    key.ds_id = entry->ds.id;
    key.gs_id = entry->gs.id;
    key.ps_id = entry->ps.id;
    key.cs_id = entry->cs.id;

    if (wine_rb_put(&priv->program_lookup, &key, &entry->program_lookup_entry) == -1)
    {
        ERR("Failed to insert program entry.\n");
    }
}