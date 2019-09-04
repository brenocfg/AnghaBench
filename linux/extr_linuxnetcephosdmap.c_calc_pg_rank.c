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
struct ceph_osds {int size; int* osds; } ;

/* Variables and functions */

__attribute__((used)) static int calc_pg_rank(int osd, const struct ceph_osds *acting)
{
	int i;

	for (i = 0; i < acting->size; i++) {
		if (acting->osds[i] == osd)
			return i;
	}

	return -1;
}