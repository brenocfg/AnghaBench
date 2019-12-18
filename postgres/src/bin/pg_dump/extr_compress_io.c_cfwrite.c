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
 int fwrite (void const*,int,int,int /*<<< orphan*/ ) ; 
 int gzwrite (scalar_t__,void const*,int) ; 

int
cfwrite(const void *ptr, int size, cfp *fp)
{
#ifdef HAVE_LIBZ
	if (fp->compressedfp)
		return gzwrite(fp->compressedfp, ptr, size);
	else
#endif
		return fwrite(ptr, 1, size, fp->uncompressedfp);
}