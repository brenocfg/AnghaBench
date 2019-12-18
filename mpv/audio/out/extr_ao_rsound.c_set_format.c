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
struct ao {int format; } ;

/* Variables and functions */
 int AF_FORMAT_S16 ; 
#define  AF_FORMAT_S32 129 
#define  AF_FORMAT_U8 128 
 int RSD_S16_NE ; 
 int RSD_S32_NE ; 
 int RSD_U8 ; 

__attribute__((used)) static int set_format(struct ao *ao)
{
    int rsd_format;

    switch (ao->format) {
    case AF_FORMAT_U8:
        rsd_format = RSD_U8;
        break;
    case AF_FORMAT_S32:
        rsd_format = RSD_S32_NE;
        break;
    default:
        rsd_format = RSD_S16_NE;
        ao->format = AF_FORMAT_S16;
    }

    return rsd_format;
}