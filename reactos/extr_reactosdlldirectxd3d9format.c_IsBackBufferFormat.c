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
typedef  scalar_t__ D3DFORMAT ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ D3DFMT_A1R5G5B5 ; 
 scalar_t__ D3DFMT_A8R8G8B8 ; 
 scalar_t__ IsExtendedFormat (scalar_t__) ; 

BOOL IsBackBufferFormat(D3DFORMAT Format)
{
    return ((Format >= D3DFMT_A8R8G8B8) && (Format < D3DFMT_A1R5G5B5)) ||
            (IsExtendedFormat(Format));
}