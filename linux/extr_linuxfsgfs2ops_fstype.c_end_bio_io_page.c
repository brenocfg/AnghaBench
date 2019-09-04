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
struct page {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_status; struct page* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void end_bio_io_page(struct bio *bio)
{
	struct page *page = bio->bi_private;

	if (!bio->bi_status)
		SetPageUptodate(page);
	else
		pr_warn("error %d reading superblock\n", bio->bi_status);
	unlock_page(page);
}