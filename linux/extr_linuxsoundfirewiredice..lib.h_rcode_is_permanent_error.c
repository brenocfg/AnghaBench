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
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_TYPE_ERROR ; 

__attribute__((used)) static inline bool rcode_is_permanent_error(int rcode)
{
	return rcode == RCODE_TYPE_ERROR || rcode == RCODE_ADDRESS_ERROR;
}