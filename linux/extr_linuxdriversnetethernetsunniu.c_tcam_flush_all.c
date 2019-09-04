#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct niu {TYPE_1__* parent; } ;
struct TYPE_2__ {unsigned long tcam_num_entries; } ;

/* Variables and functions */
 int tcam_flush (struct niu*,unsigned long) ; 

__attribute__((used)) static int tcam_flush_all(struct niu *np)
{
	unsigned long i;

	for (i = 0; i < np->parent->tcam_num_entries; i++) {
		int err = tcam_flush(np, i);
		if (err)
			return err;
	}
	return 0;
}