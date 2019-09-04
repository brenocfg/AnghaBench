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
struct vring_desc {int /*<<< orphan*/  next; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int VRING_DESC_F_NEXT ; 
 unsigned int le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned next_desc(struct vring_desc *desc)
{
	unsigned int next;

	if (!(le16toh(desc->flags) & VRING_DESC_F_NEXT))
		return -1U;
	next = le16toh(desc->next);
	return next;
}