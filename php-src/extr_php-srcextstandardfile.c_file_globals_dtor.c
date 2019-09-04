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
typedef  int /*<<< orphan*/  php_file_globals ;

/* Variables and functions */

__attribute__((used)) static void file_globals_dtor(php_file_globals *file_globals_p)
{
#if defined(HAVE_GETHOSTBYNAME_R)
	if (file_globals_p->tmp_host_buf) {
		free(file_globals_p->tmp_host_buf);
	}
#endif
}