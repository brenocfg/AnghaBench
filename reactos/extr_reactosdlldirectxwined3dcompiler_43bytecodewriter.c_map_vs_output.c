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
struct bc_writer {scalar_t__ oPos_regnum; scalar_t__ oFog_regnum; scalar_t__ oFog_mask; scalar_t__ oPts_regnum; scalar_t__ oPts_mask; scalar_t__* oD_regnum; scalar_t__* oT_regnum; int /*<<< orphan*/  state; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DSPR_ATTROUT ; 
 int /*<<< orphan*/  D3DSPR_RASTOUT ; 
 int /*<<< orphan*/  D3DSPR_TEXCRDOUT ; 
 scalar_t__ D3DSP_WRITEMASK_ALL ; 
 scalar_t__ D3DSRO_FOG ; 
 scalar_t__ D3DSRO_POINT_SIZE ; 
 scalar_t__ D3DSRO_POSITION ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 scalar_t__ d3dsp_register (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static DWORD map_vs_output(struct bc_writer *This, DWORD regnum, DWORD mask, DWORD *has_components) {
    DWORD i;

    *has_components = TRUE;
    if(regnum == This->oPos_regnum) {
        return d3dsp_register( D3DSPR_RASTOUT, D3DSRO_POSITION );
    }
    if(regnum == This->oFog_regnum && mask == This->oFog_mask) {
        *has_components = FALSE;
        return d3dsp_register( D3DSPR_RASTOUT, D3DSRO_FOG ) | D3DSP_WRITEMASK_ALL;
    }
    if(regnum == This->oPts_regnum && mask == This->oPts_mask) {
        *has_components = FALSE;
        return d3dsp_register( D3DSPR_RASTOUT, D3DSRO_POINT_SIZE ) | D3DSP_WRITEMASK_ALL;
    }
    for(i = 0; i < 2; i++) {
        if(regnum == This->oD_regnum[i]) {
            return d3dsp_register( D3DSPR_ATTROUT, i );
        }
    }
    for(i = 0; i < 8; i++) {
        if(regnum == This->oT_regnum[i]) {
            return d3dsp_register( D3DSPR_TEXCRDOUT, i );
        }
    }

    /* The varying must be undeclared - if an unsupported varying was declared,
     * the vs_find_builtin_varyings function would have caught it and this code
     * would not run */
    WARN("Undeclared varying %u\n", regnum);
    This->state = E_INVALIDARG;
    return -1;
}