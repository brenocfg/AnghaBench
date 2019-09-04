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
typedef  int D3DFORMAT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  D3DFMT_D15S1 131 
#define  D3DFMT_D24FS8 130 
#define  D3DFMT_D24S8 129 
#define  D3DFMT_D24X4S4 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL IsStencilFormat(D3DFORMAT Format)
{
    switch (Format)
    {
    case D3DFMT_D15S1:
    case D3DFMT_D24S8:
    case D3DFMT_D24X4S4:
    case D3DFMT_D24FS8:
        return TRUE;

    default:
        return FALSE;
    }
}