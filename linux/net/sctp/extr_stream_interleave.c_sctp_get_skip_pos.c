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
struct sctp_ifwdtsn_skip {scalar_t__ stream; scalar_t__ flags; } ;
typedef  scalar_t__ __u8 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */

__attribute__((used)) static inline int sctp_get_skip_pos(struct sctp_ifwdtsn_skip *skiplist,
				    int nskips, __be16 stream, __u8 flags)
{
	int i;

	for (i = 0; i < nskips; i++)
		if (skiplist[i].stream == stream &&
		    skiplist[i].flags == flags)
			return i;

	return i;
}