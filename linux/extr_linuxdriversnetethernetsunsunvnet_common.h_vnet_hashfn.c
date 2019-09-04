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
typedef  unsigned int u8 ;

/* Variables and functions */
 unsigned int VNET_PORT_HASH_MASK ; 

__attribute__((used)) static inline unsigned int vnet_hashfn(u8 *mac)
{
	unsigned int val = mac[4] ^ mac[5];

	return val & (VNET_PORT_HASH_MASK);
}