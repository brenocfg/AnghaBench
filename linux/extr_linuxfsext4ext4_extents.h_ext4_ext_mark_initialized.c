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
struct ext4_extent {int /*<<< orphan*/  ee_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_get_actual_len (struct ext4_extent*) ; 

__attribute__((used)) static inline void ext4_ext_mark_initialized(struct ext4_extent *ext)
{
	ext->ee_len = cpu_to_le16(ext4_ext_get_actual_len(ext));
}