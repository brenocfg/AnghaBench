#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  uncompressedfp; scalar_t__ compressedfp; } ;
typedef  TYPE_1__ cfp ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  READ_ERROR_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int fgetc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gzeof (scalar_t__) ; 
 int gzgetc (scalar_t__) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
cfgetc(cfp *fp)
{
	int			ret;

#ifdef HAVE_LIBZ
	if (fp->compressedfp)
	{
		ret = gzgetc(fp->compressedfp);
		if (ret == EOF)
		{
			if (!gzeof(fp->compressedfp))
				fatal("could not read from input file: %s", strerror(errno));
			else
				fatal("could not read from input file: end of file");
		}
	}
	else
#endif
	{
		ret = fgetc(fp->uncompressedfp);
		if (ret == EOF)
			READ_ERROR_EXIT(fp->uncompressedfp);
	}

	return ret;
}