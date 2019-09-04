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
typedef  int /*<<< orphan*/  substring_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int kstrtouint (char*,int,unsigned int*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fuse_match_uint(substring_t *s, unsigned int *res)
{
	int err = -ENOMEM;
	char *buf = match_strdup(s);
	if (buf) {
		err = kstrtouint(buf, 10, res);
		kfree(buf);
	}
	return err;
}