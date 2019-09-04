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
 scalar_t__ D3DFMT_A2R10G10B10 ; 

BOOL IsExtendedFormat(D3DFORMAT Format)
{
    return (Format == D3DFMT_A2R10G10B10);
}