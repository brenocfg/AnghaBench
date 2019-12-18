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
 int EOL_DOS ; 
 int EOL_MAC ; 
 int EOL_UNIX ; 
 int* p_ffs ; 

int
default_fileformat()
{
    switch (*p_ffs)
    {
	case 'm':   return EOL_MAC;
	case 'd':   return EOL_DOS;
    }
    return EOL_UNIX;
}