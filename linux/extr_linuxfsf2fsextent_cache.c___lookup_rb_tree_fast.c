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
struct rb_entry {unsigned int ofs; unsigned int len; } ;

/* Variables and functions */

__attribute__((used)) static struct rb_entry *__lookup_rb_tree_fast(struct rb_entry *cached_re,
							unsigned int ofs)
{
	if (cached_re) {
		if (cached_re->ofs <= ofs &&
				cached_re->ofs + cached_re->len > ofs) {
			return cached_re;
		}
	}
	return NULL;
}