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
 unsigned char read_data () ; 
 int /*<<< orphan*/  write_address (unsigned char) ; 

unsigned char isapnp_read_byte(unsigned char idx)
{
	write_address(idx);
	return read_data();
}