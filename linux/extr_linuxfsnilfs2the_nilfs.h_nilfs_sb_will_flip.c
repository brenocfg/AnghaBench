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
struct the_nilfs {int ns_sbwcount; } ;

/* Variables and functions */

__attribute__((used)) static inline int nilfs_sb_will_flip(struct the_nilfs *nilfs)
{
	int flip_bits = nilfs->ns_sbwcount & 0x0FL;

	return (flip_bits != 0x08 && flip_bits != 0x0F);
}