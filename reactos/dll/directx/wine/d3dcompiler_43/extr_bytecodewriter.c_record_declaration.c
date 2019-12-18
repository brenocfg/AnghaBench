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
struct declaration {scalar_t__ regnum; scalar_t__ writemask; scalar_t__ builtin; scalar_t__ mod; scalar_t__ usage_idx; scalar_t__ usage; } ;
struct bwriter_shader {unsigned int num_outputs; unsigned int num_inputs; struct declaration* inputs; struct declaration* outputs; } ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__,scalar_t__) ; 
 struct declaration* d3dcompiler_alloc (int) ; 
 struct declaration* d3dcompiler_realloc (struct declaration*,int) ; 

BOOL record_declaration(struct bwriter_shader *shader, DWORD usage,
                        DWORD usage_idx, DWORD mod, BOOL output,
                        DWORD regnum, DWORD writemask, BOOL builtin) {
    unsigned int *num;
    struct declaration **decl;
    unsigned int i;

    if(!shader) return FALSE;

    if(output) {
        num = &shader->num_outputs;
        decl = &shader->outputs;
    } else {
        num = &shader->num_inputs;
        decl = &shader->inputs;
    }

    if(*num == 0) {
        *decl = d3dcompiler_alloc(sizeof(**decl));
        if(!*decl) {
            ERR("Error allocating declarations array\n");
            return FALSE;
        }
    } else {
        struct declaration *newdecl;
        for(i = 0; i < *num; i++) {
            if((*decl)[i].regnum == regnum && ((*decl)[i].writemask & writemask)) {
                WARN("Declaration of register %u already exists, writemask match 0x%x\n",
                      regnum, (*decl)[i].writemask & writemask);
            }
        }

        newdecl = d3dcompiler_realloc(*decl,
                              sizeof(**decl) * ((*num) + 1));
        if(!newdecl) {
            ERR("Error reallocating declarations array\n");
            return FALSE;
        }
        *decl = newdecl;
    }
    (*decl)[*num].usage = usage;
    (*decl)[*num].usage_idx = usage_idx;
    (*decl)[*num].regnum = regnum;
    (*decl)[*num].mod = mod;
    (*decl)[*num].writemask = writemask;
    (*decl)[*num].builtin = builtin;
    (*num)++;

    return TRUE;
}