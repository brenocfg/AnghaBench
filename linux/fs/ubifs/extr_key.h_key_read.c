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
union ubifs_key {int /*<<< orphan*/ * j32; void** u32; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void key_read(const struct ubifs_info *c, const void *from,
			    union ubifs_key *to)
{
	const union ubifs_key *f = from;

	to->u32[0] = le32_to_cpu(f->j32[0]);
	to->u32[1] = le32_to_cpu(f->j32[1]);
}