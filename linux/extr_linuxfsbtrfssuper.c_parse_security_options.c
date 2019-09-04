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
struct security_mnt_opts {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* alloc_secdata () ; 
 int /*<<< orphan*/  free_secdata (char*) ; 
 int security_sb_copy_data (char*,char*) ; 
 int security_sb_parse_opts_str (char*,struct security_mnt_opts*) ; 

__attribute__((used)) static int parse_security_options(char *orig_opts,
				  struct security_mnt_opts *sec_opts)
{
	char *secdata = NULL;
	int ret = 0;

	secdata = alloc_secdata();
	if (!secdata)
		return -ENOMEM;
	ret = security_sb_copy_data(orig_opts, secdata);
	if (ret) {
		free_secdata(secdata);
		return ret;
	}
	ret = security_sb_parse_opts_str(secdata, sec_opts);
	free_secdata(secdata);
	return ret;
}