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
struct fpm_array_s {unsigned int sz; unsigned int allocated; scalar_t__ used; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  calloc (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  free (void*) ; 
 struct fpm_array_s* malloc (int) ; 

__attribute__((used)) static inline struct fpm_array_s *fpm_array_init(struct fpm_array_s *a, unsigned int sz, unsigned int initial_num) /* {{{ */
{
	void *allocated = 0;

	if (!a) {
		a = malloc(sizeof(struct fpm_array_s));

		if (!a) {
			return 0;
		}

		allocated = a;
	}

	a->sz = sz;

	a->data = calloc(sz, initial_num);

	if (!a->data) {
		free(allocated);
		return 0;
	}

	a->allocated = initial_num;
	a->used = 0;

	return a;
}