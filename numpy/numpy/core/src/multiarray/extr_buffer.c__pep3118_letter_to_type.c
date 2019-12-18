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
 int NPY_BOOL ; 
 int NPY_BYTE ; 
 int NPY_CDOUBLE ; 
 int NPY_CFLOAT ; 
 int NPY_CLONGDOUBLE ; 
 int NPY_DOUBLE ; 
 int NPY_FLOAT ; 
 int NPY_HALF ; 
 int NPY_INT ; 
 int NPY_INT16 ; 
 int NPY_INT32 ; 
 int NPY_INT64 ; 
 int NPY_LONG ; 
 int NPY_LONGDOUBLE ; 
 int NPY_LONGLONG ; 
 int NPY_SHORT ; 
 int NPY_UBYTE ; 
 int NPY_UINT ; 
 int NPY_UINT16 ; 
 int NPY_UINT32 ; 
 int NPY_UINT64 ; 
 int NPY_ULONG ; 
 int NPY_ULONGLONG ; 
 int NPY_USHORT ; 

__attribute__((used)) static int
_pep3118_letter_to_type(char letter, int native, int complex)
{
    switch (letter)
    {
    case '?': return NPY_BOOL;
    case 'b': return NPY_BYTE;
    case 'B': return NPY_UBYTE;
    case 'h': return native ? NPY_SHORT : NPY_INT16;
    case 'H': return native ? NPY_USHORT : NPY_UINT16;
    case 'i': return native ? NPY_INT : NPY_INT32;
    case 'I': return native ? NPY_UINT : NPY_UINT32;
    case 'l': return native ? NPY_LONG : NPY_INT32;
    case 'L': return native ? NPY_ULONG : NPY_UINT32;
    case 'q': return native ? NPY_LONGLONG : NPY_INT64;
    case 'Q': return native ? NPY_ULONGLONG : NPY_UINT64;
    case 'e': return NPY_HALF;
    case 'f': return complex ? NPY_CFLOAT : NPY_FLOAT;
    case 'd': return complex ? NPY_CDOUBLE : NPY_DOUBLE;
    case 'g': return native ? (complex ? NPY_CLONGDOUBLE : NPY_LONGDOUBLE) : -1;
    default:
        /* Other unhandled cases */
        return -1;
    }
    return -1;
}