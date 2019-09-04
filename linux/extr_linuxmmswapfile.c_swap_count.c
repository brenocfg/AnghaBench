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
 unsigned char SWAP_HAS_CACHE ; 

__attribute__((used)) static inline unsigned char swap_count(unsigned char ent)
{
	return ent & ~SWAP_HAS_CACHE;	/* may include COUNT_CONTINUED flag */
}