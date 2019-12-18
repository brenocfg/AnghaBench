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
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 int /*<<< orphan*/  min (size_t,size_t) ; 

__attribute__((used)) static int copy_sysctl_value(char *dst, size_t dst_len, char *src,
			     size_t src_len)
{
	if (!dst)
		return -EINVAL;

	if (!dst_len)
		return -E2BIG;

	if (!src || !src_len) {
		memset(dst, 0, dst_len);
		return -EINVAL;
	}

	memcpy(dst, src, min(dst_len, src_len));

	if (dst_len > src_len) {
		memset(dst + src_len, '\0', dst_len - src_len);
		return src_len;
	}

	dst[dst_len - 1] = '\0';

	return -E2BIG;
}