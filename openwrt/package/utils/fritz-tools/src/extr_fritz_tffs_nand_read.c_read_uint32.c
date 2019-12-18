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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ swap_bytes ; 

__attribute__((used)) static inline uint32_t read_uint32(void *buf, ptrdiff_t off)
{
	uint32_t tmp = *(uint32_t *)(buf + off);
	if (swap_bytes) {
		tmp = be32toh(tmp);
	}
	return tmp;
}