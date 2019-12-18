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
 int PAGE_SHIFT ; 
 int int_sqrt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  totalram_pages () ; 

__attribute__((used)) static inline int default_congestion_kb(void)
{
	int congestion_kb;

	/*
	 * Copied from NFS
	 *
	 * congestion size, scale with available memory.
	 *
	 *  64MB:    8192k
	 * 128MB:   11585k
	 * 256MB:   16384k
	 * 512MB:   23170k
	 *   1GB:   32768k
	 *   2GB:   46340k
	 *   4GB:   65536k
	 *   8GB:   92681k
	 *  16GB:  131072k
	 *
	 * This allows larger machines to have larger/more transfers.
	 * Limit the default to 256M
	 */
	congestion_kb = (16*int_sqrt(totalram_pages())) << (PAGE_SHIFT-10);
	if (congestion_kb > 256*1024)
		congestion_kb = 256*1024;

	return congestion_kb;
}