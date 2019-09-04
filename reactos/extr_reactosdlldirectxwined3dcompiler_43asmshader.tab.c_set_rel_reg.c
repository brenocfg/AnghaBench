#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct shader_reg {TYPE_2__* rel_reg; int /*<<< orphan*/  regnum; } ;
struct rel_reg {int /*<<< orphan*/  rel_regnum; int /*<<< orphan*/  swizzle; int /*<<< orphan*/  type; int /*<<< orphan*/  has_rel_reg; scalar_t__ additional_offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  swizzle; } ;
struct TYPE_4__ {int /*<<< orphan*/  regnum; TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 TYPE_2__* d3dcompiler_alloc (int) ; 

__attribute__((used)) static void set_rel_reg(struct shader_reg *reg, struct rel_reg *rel) {
    /* We can have an additional offset without true relative addressing
     * ex. c2[ 4 ] */
    reg->regnum += rel->additional_offset;
    if(!rel->has_rel_reg) {
        reg->rel_reg = NULL;
    } else {
        reg->rel_reg = d3dcompiler_alloc(sizeof(*reg->rel_reg));
        if(!reg->rel_reg) {
            return;
        }
        reg->rel_reg->type = rel->type;
        reg->rel_reg->u.swizzle = rel->swizzle;
        reg->rel_reg->regnum = rel->rel_regnum;
    }
}