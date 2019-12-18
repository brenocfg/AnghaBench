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
 int feof (int /*<<< orphan*/ ) ; 
 int gzeof (scalar_t__) ; 

int
cfeof(cfp *fp)
{
#ifdef HAVE_LIBZ
	if (fp->compressedfp)
		return gzeof(fp->compressedfp);
	else
#endif
		return feof(fp->uncompressedfp);
}