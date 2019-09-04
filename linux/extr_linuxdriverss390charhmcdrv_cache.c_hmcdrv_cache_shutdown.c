#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ofs; scalar_t__ len; int /*<<< orphan*/  fsize; int /*<<< orphan*/  id; int /*<<< orphan*/ * content; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMCDRV_FTP_NOOP ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__ hmcdrv_cache_file ; 
 int /*<<< orphan*/  hmcdrv_cache_order ; 

void hmcdrv_cache_shutdown(void)
{
	if (hmcdrv_cache_file.content) {
		free_pages((unsigned long) hmcdrv_cache_file.content,
			   hmcdrv_cache_order);
		hmcdrv_cache_file.content = NULL;
	}

	hmcdrv_cache_file.id = HMCDRV_FTP_NOOP;
	hmcdrv_cache_file.fsize = LLONG_MAX;
	hmcdrv_cache_file.ofs = -1;
	hmcdrv_cache_file.len = 0; /* no cache */
}