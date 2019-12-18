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
typedef  scalar_t__ pgoff_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 

bool
checkSeek(FILE *fp)
{
	pgoff_t		tpos;

	/*
	 * If pgoff_t is wider than long, we must have "real" fseeko and not an
	 * emulation using fseek.  Otherwise report no seek capability.
	 */
#ifndef HAVE_FSEEKO
	if (sizeof(pgoff_t) > sizeof(long))
		return false;
#endif

	/* Check that ftello works on this file */
	tpos = ftello(fp);
	if (tpos < 0)
		return false;

	/*
	 * Check that fseeko(SEEK_SET) works, too.  NB: we used to try to test
	 * this with fseeko(fp, 0, SEEK_CUR).  But some platforms treat that as a
	 * successful no-op even on files that are otherwise unseekable.
	 */
	if (fseeko(fp, tpos, SEEK_SET) != 0)
		return false;

	return true;
}