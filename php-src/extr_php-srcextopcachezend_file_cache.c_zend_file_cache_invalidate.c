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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int /*<<< orphan*/  efree (char*) ; 
 char* zend_file_cache_get_bin_file_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_file_cache_unlink (char*) ; 

void zend_file_cache_invalidate(zend_string *full_path)
{
	char *filename;

	filename = zend_file_cache_get_bin_file_path(full_path);

	zend_file_cache_unlink(filename);
	efree(filename);
}