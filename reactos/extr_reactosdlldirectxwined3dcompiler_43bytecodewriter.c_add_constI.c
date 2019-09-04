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
struct bwriter_shader {int num_ci; struct constant** constI; } ;
struct TYPE_2__ {void* i; } ;
typedef  void* INT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 void* d3dcompiler_alloc (int) ; 
 struct constant** d3dcompiler_realloc (struct constant**,int) ; 

BOOL add_constI(struct bwriter_shader *shader, DWORD reg, INT x, INT y, INT z, INT w) {
    struct constant *newconst;

    if(shader->num_ci) {
        struct constant **newarray;
        newarray = d3dcompiler_realloc(shader->constI,
                               sizeof(*shader->constI) * (shader->num_ci + 1));
        if(!newarray) {
            ERR("Failed to grow the constants array\n");
            return FALSE;
        }
        shader->constI = newarray;
    } else {
        shader->constI = d3dcompiler_alloc(sizeof(*shader->constI));
        if(!shader->constI) {
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
    newconst->value[0].i = x;
    newconst->value[1].i = y;
    newconst->value[2].i = z;
    newconst->value[3].i = w;
    shader->constI[shader->num_ci] = newconst;

    shader->num_ci++;
    return TRUE;
}