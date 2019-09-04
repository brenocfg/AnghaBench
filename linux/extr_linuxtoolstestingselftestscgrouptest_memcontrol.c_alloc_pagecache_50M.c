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
 int /*<<< orphan*/  MB (int) ; 
 int alloc_pagecache (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_pagecache_50M(const char *cgroup, void *arg)
{
	int fd = (long)arg;

	return alloc_pagecache(fd, MB(50));
}