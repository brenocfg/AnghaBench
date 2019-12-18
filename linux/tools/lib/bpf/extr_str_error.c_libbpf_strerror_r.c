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
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int strerror_r (int,char*,int) ; 

char *libbpf_strerror_r(int err, char *dst, int len)
{
	int ret = strerror_r(err < 0 ? -err : err, dst, len);
	if (ret)
		snprintf(dst, len, "ERROR: strerror_r(%d)=%d", err, ret);
	return dst;
}