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
 int BFS_NAMELEN ; 
 int /*<<< orphan*/  memcmp (unsigned char const*,char const*,int) ; 

__attribute__((used)) static inline int bfs_namecmp(int len, const unsigned char *name,
							const char *buffer)
{
	if ((len < BFS_NAMELEN) && buffer[len])
		return 0;
	return !memcmp(name, buffer, len);
}