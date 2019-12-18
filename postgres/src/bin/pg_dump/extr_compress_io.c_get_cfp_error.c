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
struct TYPE_3__ {scalar_t__ compressedfp; } ;
typedef  TYPE_1__ cfp ;

/* Variables and functions */
 int Z_ERRNO ; 
 int /*<<< orphan*/  errno ; 
 char* gzerror (scalar_t__,int*) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

const char *
get_cfp_error(cfp *fp)
{
#ifdef HAVE_LIBZ
	if (fp->compressedfp)
	{
		int			errnum;
		const char *errmsg = gzerror(fp->compressedfp, &errnum);

		if (errnum != Z_ERRNO)
			return errmsg;
	}
#endif
	return strerror(errno);
}