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
 int DDPCAPS_1BIT ; 
 int DDPCAPS_2BIT ; 
 int DDPCAPS_4BIT ; 
 int DDPCAPS_8BIT ; 
 int DDPCAPS_8BITENTRIES ; 
 int DDPCAPS_ALLOW256 ; 
 int DDPCAPS_ALPHA ; 
 int DDRAWIPAL_16 ; 
 int DDRAWIPAL_2 ; 
 int DDRAWIPAL_256 ; 
 int DDRAWIPAL_4 ; 
 int DDRAWIPAL_ALLOW256 ; 
 int DDRAWIPAL_ALPHA ; 
 int DDRAWIPAL_STORED_8INDEX ; 

DWORD ConvertPCapsFlags(DWORD dwFlags)
{
    DWORD ret = 0;
    if(dwFlags & DDPCAPS_4BIT)
        ret|=DDRAWIPAL_16;
    if(dwFlags & DDPCAPS_8BIT)
        ret|=DDRAWIPAL_256;
    if(dwFlags & DDPCAPS_8BITENTRIES)
        ret|=DDRAWIPAL_STORED_8INDEX;
    if(dwFlags & DDPCAPS_ALLOW256)
        ret|=DDRAWIPAL_ALLOW256;
    if(dwFlags & DDPCAPS_ALPHA)
        ret|=DDRAWIPAL_ALPHA;
    if(dwFlags & DDPCAPS_1BIT)
        ret|=DDRAWIPAL_2;
    if(dwFlags & DDPCAPS_2BIT)
        ret|=DDRAWIPAL_4;

    return ret;
}