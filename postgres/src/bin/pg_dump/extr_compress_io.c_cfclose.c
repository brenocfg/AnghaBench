#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * uncompressedfp; int /*<<< orphan*/ * compressedfp; } ;
typedef  TYPE_1__ cfp ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int EOF ; 
 int /*<<< orphan*/  errno ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_keep_errno (TYPE_1__*) ; 
 int gzclose (int /*<<< orphan*/ *) ; 

int
cfclose(cfp *fp)
{
	int			result;

	if (fp == NULL)
	{
		errno = EBADF;
		return EOF;
	}
#ifdef HAVE_LIBZ
	if (fp->compressedfp)
	{
		result = gzclose(fp->compressedfp);
		fp->compressedfp = NULL;
	}
	else
#endif
	{
		result = fclose(fp->uncompressedfp);
		fp->uncompressedfp = NULL;
	}
	free_keep_errno(fp);

	return result;
}