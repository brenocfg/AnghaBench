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
typedef  int VARTYPE ;

/* Variables and functions */
 unsigned char FC_DOUBLE ; 
 unsigned char FC_FLOAT ; 
 unsigned char FC_HYPER ; 
 unsigned char FC_LONG ; 
 unsigned char FC_SHORT ; 
 unsigned char FC_SMALL ; 
 unsigned char FC_ULONG ; 
 unsigned char FC_USHORT ; 
 unsigned char FC_USMALL ; 
#define  VT_BOOL 143 
#define  VT_DATE 142 
#define  VT_ERROR 141 
#define  VT_HRESULT 140 
#define  VT_I1 139 
#define  VT_I2 138 
#define  VT_I4 137 
#define  VT_I8 136 
#define  VT_INT 135 
#define  VT_R4 134 
#define  VT_R8 133 
#define  VT_UI1 132 
#define  VT_UI2 131 
#define  VT_UI4 130 
#define  VT_UI8 129 
#define  VT_UINT 128 

__attribute__((used)) static unsigned char get_base_type(VARTYPE vt)
{
    switch (vt)
    {
    case VT_I1:     return FC_SMALL;
    case VT_BOOL:
    case VT_I2:     return FC_SHORT;
    case VT_INT:
    case VT_ERROR:
    case VT_HRESULT:
    case VT_I4:     return FC_LONG;
    case VT_I8:
    case VT_UI8:    return FC_HYPER;
    case VT_UI1:    return FC_USMALL;
    case VT_UI2:    return FC_USHORT;
    case VT_UINT:
    case VT_UI4:    return FC_ULONG;
    case VT_R4:     return FC_FLOAT;
    case VT_DATE:
    case VT_R8:     return FC_DOUBLE;
    default:        return 0;
    }
}