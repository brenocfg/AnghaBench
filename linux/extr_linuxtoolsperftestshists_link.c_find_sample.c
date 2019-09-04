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
struct thread {int dummy; } ;
struct symbol {int dummy; } ;
struct sample {struct symbol* sym; struct map* map; struct thread* thread; } ;
struct map {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int find_sample(struct sample *samples, size_t nr_samples,
		       struct thread *t, struct map *m, struct symbol *s)
{
	while (nr_samples--) {
		if (samples->thread == t && samples->map == m &&
		    samples->sym == s)
			return 1;
		samples++;
	}
	return 0;
}