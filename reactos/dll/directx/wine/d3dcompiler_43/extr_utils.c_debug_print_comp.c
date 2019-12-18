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
#define  BWRITER_COMPARISON_EQ 134 
#define  BWRITER_COMPARISON_GE 133 
#define  BWRITER_COMPARISON_GT 132 
#define  BWRITER_COMPARISON_LE 131 
#define  BWRITER_COMPARISON_LT 130 
#define  BWRITER_COMPARISON_NE 129 
#define  BWRITER_COMPARISON_NONE 128 

const char *debug_print_comp(DWORD comp)
{
    switch (comp)
    {
        case BWRITER_COMPARISON_NONE: return "";
        case BWRITER_COMPARISON_GT:   return "_gt";
        case BWRITER_COMPARISON_EQ:   return "_eq";
        case BWRITER_COMPARISON_GE:   return "_ge";
        case BWRITER_COMPARISON_LT:   return "_lt";
        case BWRITER_COMPARISON_NE:   return "_ne";
        case BWRITER_COMPARISON_LE:   return "_le";
        default: return "_unknown";
    }
}