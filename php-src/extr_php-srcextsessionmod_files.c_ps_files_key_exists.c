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
typedef  int /*<<< orphan*/  zend_stat_t ;
typedef  int /*<<< orphan*/  ps_files ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int FAILURE ; 
 int MAXPATHLEN ; 
 int SUCCESS ; 
 scalar_t__ VCWD_STAT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps_files_path_create (char*,int,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int ps_files_key_exists(ps_files *data, const char *key)
{
	char buf[MAXPATHLEN];
	zend_stat_t sbuf;

	if (!key || !ps_files_path_create(buf, sizeof(buf), data, key)) {
		return FAILURE;
	}
	if (VCWD_STAT(buf, &sbuf)) {
		return FAILURE;
	}
	return SUCCESS;
}