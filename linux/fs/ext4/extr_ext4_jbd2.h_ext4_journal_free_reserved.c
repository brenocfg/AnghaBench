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
 scalar_t__ ext4_handle_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_free_reserved (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ext4_journal_free_reserved(handle_t *handle)
{
	if (ext4_handle_valid(handle))
		jbd2_journal_free_reserved(handle);
}