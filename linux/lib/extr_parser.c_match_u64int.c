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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  substring_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int kstrtoull (char*,int,int /*<<< orphan*/ *) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int match_u64int(substring_t *s, u64 *result, int base)
{
	char *buf;
	int ret;
	u64 val;

	buf = match_strdup(s);
	if (!buf)
		return -ENOMEM;

	ret = kstrtoull(buf, base, &val);
	if (!ret)
		*result = val;
	kfree(buf);
	return ret;
}