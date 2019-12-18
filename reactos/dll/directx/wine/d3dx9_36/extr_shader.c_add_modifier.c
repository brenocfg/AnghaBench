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
 int D3DSPDM_MSAMPCENTROID ; 
 int D3DSPDM_PARTIALPRECISION ; 
 int D3DSPDM_SATURATE ; 
 int D3DSP_DSTMOD_MASK ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static int add_modifier(char *buffer, DWORD param)
{
    char *buf = buffer;
    DWORD dst_mod = param & D3DSP_DSTMOD_MASK;

    if (dst_mod & D3DSPDM_SATURATE)
        buf += sprintf(buf, "_sat");
    if (dst_mod & D3DSPDM_PARTIALPRECISION)
        buf += sprintf(buf, "_pp");
    if (dst_mod & D3DSPDM_MSAMPCENTROID)
        buf += sprintf(buf, "_centroid");

    return buf - buffer;
}