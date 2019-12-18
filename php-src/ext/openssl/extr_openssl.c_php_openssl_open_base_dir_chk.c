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

/* Variables and functions */
 scalar_t__ php_check_open_basedir (char*) ; 

__attribute__((used)) inline static int php_openssl_open_base_dir_chk(char *filename)
{
	if (php_check_open_basedir(filename)) {
		return -1;
	}

	return 0;
}