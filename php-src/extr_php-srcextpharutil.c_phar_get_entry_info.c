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
typedef  int /*<<< orphan*/  phar_entry_info ;
typedef  int /*<<< orphan*/  phar_archive_data ;

/* Variables and functions */
 int /*<<< orphan*/ * phar_get_entry_info_dir (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ,char**,int) ; 

phar_entry_info *phar_get_entry_info(phar_archive_data *phar, char *path, size_t path_len, char **error, int security) /* {{{ */
{
	return phar_get_entry_info_dir(phar, path, path_len, 0, error, security);
}