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
struct TYPE_3__ {int fd; } ;
typedef  TYPE_1__ ps_files ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_UN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  flock (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps_files_close(ps_files *data)
{
	if (data->fd != -1) {
#ifdef PHP_WIN32
		/* On Win32 locked files that are closed without being explicitly unlocked
		   will be unlocked only when "system resources become available". */
		flock(data->fd, LOCK_UN);
#endif
		close(data->fd);
		data->fd = -1;
	}
}