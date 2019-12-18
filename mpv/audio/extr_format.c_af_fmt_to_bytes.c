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
#define  AF_FORMAT_DOUBLE 133 
#define  AF_FORMAT_FLOAT 132 
#define  AF_FORMAT_S16 131 
#define  AF_FORMAT_S32 130 
#define  AF_FORMAT_S64 129 
#define  AF_FORMAT_U8 128 
 int af_fmt_from_planar (int) ; 
 scalar_t__ af_fmt_is_spdif (int) ; 

int af_fmt_to_bytes(int format)
{
    switch (af_fmt_from_planar(format)) {
    case AF_FORMAT_U8:      return 1;
    case AF_FORMAT_S16:     return 2;
    case AF_FORMAT_S32:     return 4;
    case AF_FORMAT_S64:     return 8;
    case AF_FORMAT_FLOAT:   return 4;
    case AF_FORMAT_DOUBLE:  return 8;
    }
    if (af_fmt_is_spdif(format))
        return 2;
    return 0;
}