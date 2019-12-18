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
struct vring_used_elem {int dummy; } ;
struct vring_desc {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */

__attribute__((used)) static inline unsigned _vring_size(unsigned int num, unsigned long align)
{
	return ((sizeof(struct vring_desc) * num + sizeof(__u16) * (3 + num)
				+ align - 1) & ~(align - 1))
		+ sizeof(__u16) * 3 + sizeof(struct vring_used_elem) * num;
}