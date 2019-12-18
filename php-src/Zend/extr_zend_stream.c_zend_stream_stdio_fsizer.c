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
struct TYPE_3__ {size_t st_size; int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ zend_stat_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_fstat (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static size_t zend_stream_stdio_fsizer(void *handle) /* {{{ */
{
	zend_stat_t buf;
	if (handle && zend_fstat(fileno((FILE*)handle), &buf) == 0) {
#ifdef S_ISREG
		if (!S_ISREG(buf.st_mode)) {
			return 0;
		}
#endif
		return buf.st_size;
	}
	return -1;
}