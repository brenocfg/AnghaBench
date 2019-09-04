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
struct nilfs_sc_info {int /*<<< orphan*/  sc_write_logs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_destroy_logs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_segctor_complete_write (struct nilfs_sc_info*) ; 
 int nilfs_wait_on_logs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_segctor_wait(struct nilfs_sc_info *sci)
{
	int ret;

	ret = nilfs_wait_on_logs(&sci->sc_write_logs);
	if (!ret) {
		nilfs_segctor_complete_write(sci);
		nilfs_destroy_logs(&sci->sc_write_logs);
	}
	return ret;
}