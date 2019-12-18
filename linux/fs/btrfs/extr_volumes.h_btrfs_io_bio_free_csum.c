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
struct btrfs_io_bio {int /*<<< orphan*/ * csum; int /*<<< orphan*/ * csum_inline; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void btrfs_io_bio_free_csum(struct btrfs_io_bio *io_bio)
{
	if (io_bio->csum != io_bio->csum_inline) {
		kfree(io_bio->csum);
		io_bio->csum = NULL;
	}
}