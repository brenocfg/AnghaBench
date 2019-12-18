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

/* Variables and functions */
#define  BOOL_FUNCTION 133 
#define  EMPTY 132 
#define  IDENTIFIER 131 
#define  INTEGER 130 
#define  STRING 129 
#define  VOID_FUNCTION 128 

__attribute__((used)) static const char* ts(int t)
{
    static char c[2] = {0,0};

    switch (t)
    {
    case EMPTY: return "EMPTY";
    case VOID_FUNCTION: return "VOID_FUNCTION";
    case BOOL_FUNCTION: return "BOOL_FUNCTION";
    case INTEGER: return "INTEGER";
    case STRING: return "STRING";
    case IDENTIFIER: return "IDENTIFIER";
    default: c[0] = (char)t; return c;
    }
}