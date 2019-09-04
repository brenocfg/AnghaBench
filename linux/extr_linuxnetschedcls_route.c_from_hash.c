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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 from_hash(u32 id)
{
	id &= 0xFFFF;
	if (id == 0xFFFF)
		return 32;
	if (!(id & 0x8000)) {
		if (id > 255)
			return 256;
		return id & 0xF;
	}
	return 16 + (id & 0xF);
}