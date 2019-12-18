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
struct f2fs_sb_info {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAULT_ALLOC_BIO ; 
 int GFP_KERNEL ; 
 int GFP_NOIO ; 
 int __GFP_NOFAIL ; 
 struct bio* bio_alloc (int,int) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 scalar_t__ time_to_inject (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct bio *f2fs_bio_alloc(struct f2fs_sb_info *sbi,
						int npages, bool no_fail)
{
	struct bio *bio;

	if (no_fail) {
		/* No failure on bio allocation */
		bio = bio_alloc(GFP_NOIO, npages);
		if (!bio)
			bio = bio_alloc(GFP_NOIO | __GFP_NOFAIL, npages);
		return bio;
	}
	if (time_to_inject(sbi, FAULT_ALLOC_BIO)) {
		f2fs_show_injection_info(FAULT_ALLOC_BIO);
		return NULL;
	}

	return bio_alloc(GFP_KERNEL, npages);
}