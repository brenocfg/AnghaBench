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
struct instruction {int dummy; } ;
struct bwriter_shader {int instr_alloc_size; int num_instrs; struct instruction** instr; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int INSTRARRAY_INITIAL_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 struct instruction** d3dcompiler_alloc (int) ; 
 struct instruction** d3dcompiler_realloc (struct instruction**,int) ; 

BOOL add_instruction(struct bwriter_shader *shader, struct instruction *instr) {
    struct instruction      **new_instructions;

    if(!shader) return FALSE;

    if(shader->instr_alloc_size == 0) {
        shader->instr = d3dcompiler_alloc(sizeof(*shader->instr) * INSTRARRAY_INITIAL_SIZE);
        if(!shader->instr) {
            ERR("Failed to allocate the shader instruction array\n");
            return FALSE;
        }
        shader->instr_alloc_size = INSTRARRAY_INITIAL_SIZE;
    } else if(shader->instr_alloc_size == shader->num_instrs) {
        new_instructions = d3dcompiler_realloc(shader->instr,
                                       sizeof(*shader->instr) * (shader->instr_alloc_size) * 2);
        if(!new_instructions) {
            ERR("Failed to grow the shader instruction array\n");
            return FALSE;
        }
        shader->instr = new_instructions;
        shader->instr_alloc_size = shader->instr_alloc_size * 2;
    } else if(shader->num_instrs > shader->instr_alloc_size) {
        ERR("More instructions than allocated. This should not happen\n");
        return FALSE;
    }

    shader->instr[shader->num_instrs] = instr;
    shader->num_instrs++;
    return TRUE;
}