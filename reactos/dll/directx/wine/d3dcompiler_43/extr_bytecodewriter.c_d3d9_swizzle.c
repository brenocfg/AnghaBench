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
typedef  int DWORD ;

/* Variables and functions */
 int BWRITERVS_W_W ; 
 int BWRITERVS_W_X ; 
 int BWRITERVS_W_Y ; 
 int BWRITERVS_W_Z ; 
 int BWRITERVS_X_W ; 
 int BWRITERVS_X_X ; 
 int BWRITERVS_X_Y ; 
 int BWRITERVS_X_Z ; 
 int BWRITERVS_Y_W ; 
 int BWRITERVS_Y_X ; 
 int BWRITERVS_Y_Y ; 
 int BWRITERVS_Y_Z ; 
 int BWRITERVS_Z_W ; 
 int BWRITERVS_Z_X ; 
 int BWRITERVS_Z_Y ; 
 int BWRITERVS_Z_Z ; 
 int D3DVS_W_W ; 
 int D3DVS_W_X ; 
 int D3DVS_W_Y ; 
 int D3DVS_W_Z ; 
 int D3DVS_X_W ; 
 int D3DVS_X_X ; 
 int D3DVS_X_Y ; 
 int D3DVS_X_Z ; 
 int D3DVS_Y_W ; 
 int D3DVS_Y_X ; 
 int D3DVS_Y_Y ; 
 int D3DVS_Y_Z ; 
 int D3DVS_Z_W ; 
 int D3DVS_Z_X ; 
 int D3DVS_Z_Y ; 
 int D3DVS_Z_Z ; 

__attribute__((used)) static DWORD d3d9_swizzle(DWORD bwriter_swizzle)
{
    /* Currently a NOP, but this allows changing the internal definitions
     * without side effects. */
    DWORD ret = 0;

    if ((bwriter_swizzle & BWRITERVS_X_X) == BWRITERVS_X_X) ret |= D3DVS_X_X;
    if ((bwriter_swizzle & BWRITERVS_X_Y) == BWRITERVS_X_Y) ret |= D3DVS_X_Y;
    if ((bwriter_swizzle & BWRITERVS_X_Z) == BWRITERVS_X_Z) ret |= D3DVS_X_Z;
    if ((bwriter_swizzle & BWRITERVS_X_W) == BWRITERVS_X_W) ret |= D3DVS_X_W;

    if ((bwriter_swizzle & BWRITERVS_Y_X) == BWRITERVS_Y_X) ret |= D3DVS_Y_X;
    if ((bwriter_swizzle & BWRITERVS_Y_Y) == BWRITERVS_Y_Y) ret |= D3DVS_Y_Y;
    if ((bwriter_swizzle & BWRITERVS_Y_Z) == BWRITERVS_Y_Z) ret |= D3DVS_Y_Z;
    if ((bwriter_swizzle & BWRITERVS_Y_W) == BWRITERVS_Y_W) ret |= D3DVS_Y_W;

    if ((bwriter_swizzle & BWRITERVS_Z_X) == BWRITERVS_Z_X) ret |= D3DVS_Z_X;
    if ((bwriter_swizzle & BWRITERVS_Z_Y) == BWRITERVS_Z_Y) ret |= D3DVS_Z_Y;
    if ((bwriter_swizzle & BWRITERVS_Z_Z) == BWRITERVS_Z_Z) ret |= D3DVS_Z_Z;
    if ((bwriter_swizzle & BWRITERVS_Z_W) == BWRITERVS_Z_W) ret |= D3DVS_Z_W;

    if ((bwriter_swizzle & BWRITERVS_W_X) == BWRITERVS_W_X) ret |= D3DVS_W_X;
    if ((bwriter_swizzle & BWRITERVS_W_Y) == BWRITERVS_W_Y) ret |= D3DVS_W_Y;
    if ((bwriter_swizzle & BWRITERVS_W_Z) == BWRITERVS_W_Z) ret |= D3DVS_W_Z;
    if ((bwriter_swizzle & BWRITERVS_W_W) == BWRITERVS_W_W) ret |= D3DVS_W_W;

    return ret;
}