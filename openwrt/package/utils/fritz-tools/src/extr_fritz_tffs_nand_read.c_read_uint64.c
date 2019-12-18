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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 scalar_t__ swap_bytes ; 

__attribute__((used)) static inline uint64_t read_uint64(void *buf, ptrdiff_t off)
{
	uint64_t tmp = *(uint64_t *)(buf + off);
	if (swap_bytes) {
		tmp = be64toh(tmp);
	}
	return tmp;
}