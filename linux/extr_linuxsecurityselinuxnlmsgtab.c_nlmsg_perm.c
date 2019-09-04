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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct nlmsg_perm {scalar_t__ nlmsg_type; int /*<<< orphan*/  perm; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int nlmsg_perm(u16 nlmsg_type, u32 *perm, const struct nlmsg_perm *tab, size_t tabsize)
{
	int i, err = -EINVAL;

	for (i = 0; i < tabsize/sizeof(struct nlmsg_perm); i++)
		if (nlmsg_type == tab[i].nlmsg_type) {
			*perm = tab[i].perm;
			err = 0;
			break;
		}

	return err;
}