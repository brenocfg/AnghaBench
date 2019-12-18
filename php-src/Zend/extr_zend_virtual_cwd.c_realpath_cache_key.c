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
typedef  int /*<<< orphan*/  zend_ulong ;

/* Variables and functions */
 int /*<<< orphan*/  Z_UL (int) ; 

__attribute__((used)) static inline zend_ulong realpath_cache_key(const char *path, size_t path_len) /* {{{ */
{
	register zend_ulong h;
	const char *e = path + path_len;

	for (h = Z_UL(2166136261); path < e;) {
		h *= Z_UL(16777619);
		h ^= *path++;
	}

	return h;
}