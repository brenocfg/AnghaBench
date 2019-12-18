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
struct bio {int /*<<< orphan*/  bi_status; scalar_t__ bi_private; } ;

/* Variables and functions */

__attribute__((used)) static bool f2fs_bio_post_read_required(struct bio *bio)
{
	return bio->bi_private && !bio->bi_status;
}