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
struct dlm_cluster {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static ssize_t cluster_set(struct dlm_cluster *cl, unsigned int *cl_field,
			   int *info_field, int check_zero,
			   const char *buf, size_t len)
{
	unsigned int x;
	int rc;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	rc = kstrtouint(buf, 0, &x);
	if (rc)
		return rc;

	if (check_zero && !x)
		return -EINVAL;

	*cl_field = x;
	*info_field = x;

	return len;
}