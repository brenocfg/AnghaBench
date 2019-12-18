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
 scalar_t__ ERR_GET_REASON (unsigned long) ; 
 unsigned long ERR_get_error () ; 
 scalar_t__ RSA_R_UNKNOWN_PADDING_TYPE ; 

__attribute__((used)) static int pad_unknown(void)
{
    unsigned long l;
    while ((l = ERR_get_error()) != 0)
        if (ERR_GET_REASON(l) == RSA_R_UNKNOWN_PADDING_TYPE)
            return 1;
    return 0;
}