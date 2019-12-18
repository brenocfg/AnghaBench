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
 int /*<<< orphan*/  NILFS_TI_WRITER ; 
 int nilfs_test_transaction_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int nilfs_doing_construction(void)
{
	return nilfs_test_transaction_flag(NILFS_TI_WRITER);
}