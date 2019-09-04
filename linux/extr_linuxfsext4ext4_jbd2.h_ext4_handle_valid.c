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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 unsigned long EXT4_NOJOURNAL_MAX_REF_COUNT ; 

__attribute__((used)) static inline int ext4_handle_valid(handle_t *handle)
{
	if ((unsigned long)handle < EXT4_NOJOURNAL_MAX_REF_COUNT)
		return 0;
	return 1;
}