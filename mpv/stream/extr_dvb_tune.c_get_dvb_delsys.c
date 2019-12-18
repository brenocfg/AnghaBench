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
 unsigned int SYS_DVB__COUNT__ ; 
 char const** dvb_delsys_str ; 

const char *get_dvb_delsys(unsigned int delsys)
{
    if (SYS_DVB__COUNT__ <= delsys)
        return dvb_delsys_str[0];
    return dvb_delsys_str[delsys];
}