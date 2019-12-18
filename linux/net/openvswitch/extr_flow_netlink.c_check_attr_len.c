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
 unsigned int OVS_ATTR_NESTED ; 
 unsigned int OVS_ATTR_VARIABLE ; 

__attribute__((used)) static bool check_attr_len(unsigned int attr_len, unsigned int expected_len)
{
	return expected_len == attr_len ||
	       expected_len == OVS_ATTR_NESTED ||
	       expected_len == OVS_ATTR_VARIABLE;
}