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
struct shader_reg {scalar_t__ regnum; } ;
struct bc_writer {scalar_t__* v_regnum; scalar_t__* t_regnum; int /*<<< orphan*/  state; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DSPR_INPUT ; 
 int /*<<< orphan*/  D3DSPR_TEXTURE ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int d3dsp_register (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static DWORD map_ps_input(struct bc_writer *This,
                          const struct shader_reg *reg) {
    DWORD i;
    /* Map color interpolators */
    for(i = 0; i < 2; i++) {
        if(reg->regnum == This->v_regnum[i]) {
            return d3dsp_register( D3DSPR_INPUT, i );
        }
    }
    for(i = 0; i < 8; i++) {
        if(reg->regnum == This->t_regnum[i]) {
            return d3dsp_register( D3DSPR_TEXTURE, i );
        }
    }

    WARN("Invalid ps 1/2 varying\n");
    This->state = E_INVALIDARG;
    return 0;
}