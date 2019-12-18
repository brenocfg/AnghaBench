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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/ * Walfile ;
struct TYPE_4__ {scalar_t__ compression; } ;
struct TYPE_3__ {int /*<<< orphan*/  currpos; int /*<<< orphan*/  fd; int /*<<< orphan*/  gzfp; } ;
typedef  TYPE_1__ DirectoryMethodFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* dir_data ; 
 scalar_t__ gzwrite (int /*<<< orphan*/ ,void const*,size_t) ; 
 scalar_t__ write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static ssize_t
dir_write(Walfile f, const void *buf, size_t count)
{
	ssize_t		r;
	DirectoryMethodFile *df = (DirectoryMethodFile *) f;

	Assert(f != NULL);

#ifdef HAVE_LIBZ
	if (dir_data->compression > 0)
		r = (ssize_t) gzwrite(df->gzfp, buf, count);
	else
#endif
		r = write(df->fd, buf, count);
	if (r > 0)
		df->currpos += r;
	return r;
}