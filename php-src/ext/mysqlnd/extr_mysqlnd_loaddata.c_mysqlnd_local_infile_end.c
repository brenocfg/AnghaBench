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
struct TYPE_3__ {int /*<<< orphan*/ * fd; } ;
typedef  TYPE_1__ MYSQLND_INFILE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  mnd_efree (TYPE_1__*) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void mysqlnd_local_infile_end(void * ptr)
{
	MYSQLND_INFILE_INFO	*info = (MYSQLND_INFILE_INFO *)ptr;

	if (info) {
		/* php_stream_close segfaults on NULL */
		if (info->fd) {
			php_stream_close(info->fd);
			info->fd = NULL;
		}
		mnd_efree(info);
	}
}