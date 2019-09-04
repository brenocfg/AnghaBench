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
 int BWRITERSPDM_MSAMPCENTROID ; 
 int BWRITERSPDM_PARTIALPRECISION ; 
 int BWRITERSPDM_SATURATE ; 
 int D3DSPDM_MSAMPCENTROID ; 
 int D3DSPDM_PARTIALPRECISION ; 
 int D3DSPDM_SATURATE ; 

__attribute__((used)) static DWORD d3d9_dstmod(DWORD bwriter_mod)
{
    DWORD ret = 0;

    if (bwriter_mod & BWRITERSPDM_SATURATE)         ret |= D3DSPDM_SATURATE;
    if (bwriter_mod & BWRITERSPDM_PARTIALPRECISION) ret |= D3DSPDM_PARTIALPRECISION;
    if (bwriter_mod & BWRITERSPDM_MSAMPCENTROID)    ret |= D3DSPDM_MSAMPCENTROID;

    return ret;
}