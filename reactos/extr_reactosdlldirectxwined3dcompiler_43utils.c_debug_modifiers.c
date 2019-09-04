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
 int HLSL_MODIFIER_COLUMN_MAJOR ; 
 int HLSL_MODIFIER_CONST ; 
 int HLSL_MODIFIER_IN ; 
 int HLSL_MODIFIER_OUT ; 
 int HLSL_MODIFIER_PRECISE ; 
 int HLSL_MODIFIER_ROW_MAJOR ; 
 int HLSL_STORAGE_EXTERN ; 
 int HLSL_STORAGE_GROUPSHARED ; 
 int HLSL_STORAGE_NOINTERPOLATION ; 
 int HLSL_STORAGE_SHARED ; 
 int HLSL_STORAGE_STATIC ; 
 int HLSL_STORAGE_UNIFORM ; 
 int HLSL_STORAGE_VOLATILE ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char const* wine_dbg_sprintf (char*,char*) ; 

const char *debug_modifiers(DWORD modifiers)
{
    char string[110];

    string[0] = 0;
    if (modifiers & HLSL_STORAGE_EXTERN)
        strcat(string, " extern");                       /* 7 */
    if (modifiers & HLSL_STORAGE_NOINTERPOLATION)
        strcat(string, " nointerpolation");              /* 16 */
    if (modifiers & HLSL_MODIFIER_PRECISE)
        strcat(string, " precise");                      /* 8 */
    if (modifiers & HLSL_STORAGE_SHARED)
        strcat(string, " shared");                       /* 7 */
    if (modifiers & HLSL_STORAGE_GROUPSHARED)
        strcat(string, " groupshared");                  /* 12 */
    if (modifiers & HLSL_STORAGE_STATIC)
        strcat(string, " static");                       /* 7 */
    if (modifiers & HLSL_STORAGE_UNIFORM)
        strcat(string, " uniform");                      /* 8 */
    if (modifiers & HLSL_STORAGE_VOLATILE)
        strcat(string, " volatile");                     /* 9 */
    if (modifiers & HLSL_MODIFIER_CONST)
        strcat(string, " const");                        /* 6 */
    if (modifiers & HLSL_MODIFIER_ROW_MAJOR)
        strcat(string, " row_major");                    /* 10 */
    if (modifiers & HLSL_MODIFIER_COLUMN_MAJOR)
        strcat(string, " column_major");                 /* 13 */
    if ((modifiers & (HLSL_MODIFIER_IN | HLSL_MODIFIER_OUT)) == (HLSL_MODIFIER_IN | HLSL_MODIFIER_OUT))
        strcat(string, " inout");                        /* 6 */
    else if (modifiers & HLSL_MODIFIER_IN)
        strcat(string, " in");                           /* 3 */
    else if (modifiers & HLSL_MODIFIER_OUT)
        strcat(string, " out");                          /* 4 */

    return wine_dbg_sprintf("%s", string[0] ? string + 1 : "");
}