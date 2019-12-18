#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_texture {int dummy; } ;
struct wined3d_color_key {int dummy; } ;
struct wined3d_cs_set_color_key {int set; struct wined3d_color_key color_key; int /*<<< orphan*/  flags; struct wined3d_texture* texture; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_2__ {int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_set_color_key* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_CS_OP_SET_COLOR_KEY ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 struct wined3d_cs_set_color_key* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 

void wined3d_cs_emit_set_color_key(struct wined3d_cs *cs, struct wined3d_texture *texture,
        WORD flags, const struct wined3d_color_key *color_key)
{
    struct wined3d_cs_set_color_key *op;

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_DEFAULT);
    op->opcode = WINED3D_CS_OP_SET_COLOR_KEY;
    op->texture = texture;
    op->flags = flags;
    if (color_key)
    {
        op->color_key = *color_key;
        op->set = 1;
    }
    else
        op->set = 0;

    cs->ops->submit(cs, WINED3D_CS_QUEUE_DEFAULT);
}