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
struct TYPE_4__ {int cached_fstat; int /*<<< orphan*/  sb; int /*<<< orphan*/  no_forced_fstat; } ;
typedef  TYPE_1__ php_stdio_stream_data ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_STDIOP_GET_FD (int,TYPE_1__*) ; 
 int zend_fstat (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_fstat(php_stdio_stream_data *d, int force)
{
	if (!d->cached_fstat || (force && !d->no_forced_fstat)) {
		int fd;
		int r;

		PHP_STDIOP_GET_FD(fd, d);
		r = zend_fstat(fd, &d->sb);
		d->cached_fstat = r == 0;

		return r;
	}
	return 0;
}