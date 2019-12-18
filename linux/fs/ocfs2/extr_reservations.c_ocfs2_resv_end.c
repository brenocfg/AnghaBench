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
struct ocfs2_alloc_reservation {unsigned int r_len; unsigned int r_start; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int ocfs2_resv_end(struct ocfs2_alloc_reservation *resv)
{
	if (resv->r_len)
		return resv->r_start + resv->r_len - 1;
	return resv->r_start;
}