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
 int /*<<< orphan*/  READ_ERROR_EXIT (int /*<<< orphan*/ ) ; 
 int Z_ERRNO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 int fread (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gzeof (scalar_t__) ; 
 char* gzerror (scalar_t__,int*) ; 
 int gzread (scalar_t__,void*,int) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

int
cfread(void *ptr, int size, cfp *fp)
{
	int			ret;

	if (size == 0)
		return 0;

#ifdef HAVE_LIBZ
	if (fp->compressedfp)
	{
		ret = gzread(fp->compressedfp, ptr, size);
		if (ret != size && !gzeof(fp->compressedfp))
		{
			int			errnum;
			const char *errmsg = gzerror(fp->compressedfp, &errnum);

			fatal("could not read from input file: %s",
				  errnum == Z_ERRNO ? strerror(errno) : errmsg);
		}
	}
	else
#endif
	{
		ret = fread(ptr, 1, size, fp->uncompressedfp);
		if (ret != size && !feof(fp->uncompressedfp))
			READ_ERROR_EXIT(fp->uncompressedfp);
	}
	return ret;
}