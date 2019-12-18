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
struct constant {TYPE_1__* value; int /*<<< orphan*/  regnum; } ;
struct bwriter_shader {int num_cb; struct constant** constB; } ;
struct TYPE_2__ {int /*<<< orphan*/  b; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 void* d3dcompiler_alloc (int) ; 
 struct constant** d3dcompiler_realloc (struct constant**,int) ; 

BOOL add_constB(struct bwriter_shader *shader, DWORD reg, BOOL x) {
    struct constant *newconst;

    if(shader->num_cb) {
        struct constant **newarray;
        newarray = d3dcompiler_realloc(shader->constB,
                               sizeof(*shader->constB) * (shader->num_cb + 1));
        if(!newarray) {
            ERR("Failed to grow the constants array\n");
            return FALSE;
        }
        shader->constB = newarray;
    } else {
        shader->constB = d3dcompiler_alloc(sizeof(*shader->constB));
        if(!shader->constB) {
            ERR("Failed to allocate the constants array\n");
            return FALSE;
        }
    }

    newconst = d3dcompiler_alloc(sizeof(*newconst));
    if(!newconst) {
        ERR("Failed to allocate a new constant\n");
        return FALSE;
    }
    newconst->regnum = reg;
    newconst->value[0].b = x;
    shader->constB[shader->num_cb] = newconst;

    shader->num_cb++;
    return TRUE;
}