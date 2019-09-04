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
typedef  scalar_t__ loff_t ;

/* Variables and functions */

__attribute__((used)) static inline bool nfsd_eof_on_read(long requested, long read,
				loff_t offset, loff_t size)
{
	/* We assume a short read means eof: */
	if (requested > read)
		return true;
	/*
	 * A non-short read might also reach end of file.  The spec
	 * still requires us to set eof in that case.
	 *
	 * Further operations may have modified the file size since
	 * the read, so the following check is not atomic with the read.
	 * We've only seen that cause a problem for a client in the case
	 * where the read returned a count of 0 without setting eof.
	 * That case was fixed by the addition of the above check.
	 */
	return (offset + read >= size);
}