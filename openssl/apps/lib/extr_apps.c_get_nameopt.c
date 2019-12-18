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
 unsigned long XN_FLAG_ONELINE ; 
 unsigned long nmflag ; 
 scalar_t__ nmflag_set ; 

unsigned long get_nameopt(void)
{
    return (nmflag_set) ? nmflag : XN_FLAG_ONELINE;
}