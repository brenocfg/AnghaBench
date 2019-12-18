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
 int /*<<< orphan*/  BWRITERSPSM_ABS ; 
 int /*<<< orphan*/  BWRITERSPSM_ABSNEG ; 
 int /*<<< orphan*/  BWRITERSPSM_BIAS ; 
 int /*<<< orphan*/  BWRITERSPSM_BIASNEG ; 
 int /*<<< orphan*/  BWRITERSPSM_COMP ; 
 int /*<<< orphan*/  BWRITERSPSM_DW ; 
 int /*<<< orphan*/  BWRITERSPSM_DZ ; 
 int /*<<< orphan*/  BWRITERSPSM_NEG ; 
 int /*<<< orphan*/  BWRITERSPSM_NOT ; 
 int /*<<< orphan*/  BWRITERSPSM_SIGN ; 
 int /*<<< orphan*/  BWRITERSPSM_SIGNNEG ; 
 int /*<<< orphan*/  BWRITERSPSM_X2 ; 
 int /*<<< orphan*/  BWRITERSPSM_X2NEG ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINE_D3DCOMPILER_TO_STR (int /*<<< orphan*/ ) ; 

const char *debug_print_srcmod(DWORD mod)
{
    switch (mod)
    {
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_NEG);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_BIAS);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_BIASNEG);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_SIGN);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_SIGNNEG);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_COMP);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_X2);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_X2NEG);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_DZ);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_DW);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_ABS);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_ABSNEG);
        WINE_D3DCOMPILER_TO_STR(BWRITERSPSM_NOT);
        default:
            FIXME("Unrecognized source modifier %#x.\n", mod);
            return "unrecognized_src_mod";
    }
}