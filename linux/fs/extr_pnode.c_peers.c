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
struct mount {scalar_t__ mnt_group_id; } ;

/* Variables and functions */

__attribute__((used)) static inline bool peers(struct mount *m1, struct mount *m2)
{
	return m1->mnt_group_id == m2->mnt_group_id && m1->mnt_group_id;
}