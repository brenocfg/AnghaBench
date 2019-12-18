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
struct seq_file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 void* saved_tgids_next (struct seq_file*,void*,scalar_t__*) ; 
 int /*<<< orphan*/ * tgid_map ; 

__attribute__((used)) static void *saved_tgids_start(struct seq_file *m, loff_t *pos)
{
	void *v;
	loff_t l = 0;

	if (!tgid_map)
		return NULL;

	v = &tgid_map[0];
	while (l <= *pos) {
		v = saved_tgids_next(m, v, &l);
		if (!v)
			return NULL;
	}

	return v;
}