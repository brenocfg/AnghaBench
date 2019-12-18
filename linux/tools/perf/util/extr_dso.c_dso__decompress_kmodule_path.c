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
struct dso {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int decompress_kmodule (struct dso*,char const*,char*,size_t) ; 

int dso__decompress_kmodule_path(struct dso *dso, const char *name,
				 char *pathname, size_t len)
{
	int fd = decompress_kmodule(dso, name, pathname, len);

	close(fd);
	return fd >= 0 ? 0 : -1;
}