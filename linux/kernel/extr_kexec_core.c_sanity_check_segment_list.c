#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kimage {unsigned long nr_segments; scalar_t__ type; TYPE_1__* segment; } ;
struct TYPE_4__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_3__ {unsigned long mem; unsigned long memsz; scalar_t__ bufsz; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 unsigned long KEXEC_DESTINATION_MEMORY_LIMIT ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 unsigned long PAGE_COUNT (scalar_t__) ; 
 unsigned long PAGE_MASK ; 
 TYPE_2__ crashk_res ; 
 unsigned long phys_to_boot_phys (int /*<<< orphan*/ ) ; 
 unsigned long totalram_pages () ; 

int sanity_check_segment_list(struct kimage *image)
{
	int i;
	unsigned long nr_segments = image->nr_segments;
	unsigned long total_pages = 0;
	unsigned long nr_pages = totalram_pages();

	/*
	 * Verify we have good destination addresses.  The caller is
	 * responsible for making certain we don't attempt to load
	 * the new image into invalid or reserved areas of RAM.  This
	 * just verifies it is an address we can use.
	 *
	 * Since the kernel does everything in page size chunks ensure
	 * the destination addresses are page aligned.  Too many
	 * special cases crop of when we don't do this.  The most
	 * insidious is getting overlapping destination addresses
	 * simply because addresses are changed to page size
	 * granularity.
	 */
	for (i = 0; i < nr_segments; i++) {
		unsigned long mstart, mend;

		mstart = image->segment[i].mem;
		mend   = mstart + image->segment[i].memsz;
		if (mstart > mend)
			return -EADDRNOTAVAIL;
		if ((mstart & ~PAGE_MASK) || (mend & ~PAGE_MASK))
			return -EADDRNOTAVAIL;
		if (mend >= KEXEC_DESTINATION_MEMORY_LIMIT)
			return -EADDRNOTAVAIL;
	}

	/* Verify our destination addresses do not overlap.
	 * If we alloed overlapping destination addresses
	 * through very weird things can happen with no
	 * easy explanation as one segment stops on another.
	 */
	for (i = 0; i < nr_segments; i++) {
		unsigned long mstart, mend;
		unsigned long j;

		mstart = image->segment[i].mem;
		mend   = mstart + image->segment[i].memsz;
		for (j = 0; j < i; j++) {
			unsigned long pstart, pend;

			pstart = image->segment[j].mem;
			pend   = pstart + image->segment[j].memsz;
			/* Do the segments overlap ? */
			if ((mend > pstart) && (mstart < pend))
				return -EINVAL;
		}
	}

	/* Ensure our buffer sizes are strictly less than
	 * our memory sizes.  This should always be the case,
	 * and it is easier to check up front than to be surprised
	 * later on.
	 */
	for (i = 0; i < nr_segments; i++) {
		if (image->segment[i].bufsz > image->segment[i].memsz)
			return -EINVAL;
	}

	/*
	 * Verify that no more than half of memory will be consumed. If the
	 * request from userspace is too large, a large amount of time will be
	 * wasted allocating pages, which can cause a soft lockup.
	 */
	for (i = 0; i < nr_segments; i++) {
		if (PAGE_COUNT(image->segment[i].memsz) > nr_pages / 2)
			return -EINVAL;

		total_pages += PAGE_COUNT(image->segment[i].memsz);
	}

	if (total_pages > nr_pages / 2)
		return -EINVAL;

	/*
	 * Verify we have good destination addresses.  Normally
	 * the caller is responsible for making certain we don't
	 * attempt to load the new image into invalid or reserved
	 * areas of RAM.  But crash kernels are preloaded into a
	 * reserved area of ram.  We must ensure the addresses
	 * are in the reserved area otherwise preloading the
	 * kernel could corrupt things.
	 */

	if (image->type == KEXEC_TYPE_CRASH) {
		for (i = 0; i < nr_segments; i++) {
			unsigned long mstart, mend;

			mstart = image->segment[i].mem;
			mend = mstart + image->segment[i].memsz - 1;
			/* Ensure we are within the crash kernel limits */
			if ((mstart < phys_to_boot_phys(crashk_res.start)) ||
			    (mend > phys_to_boot_phys(crashk_res.end)))
				return -EADDRNOTAVAIL;
		}
	}

	return 0;
}