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
typedef  int /*<<< orphan*/  Bucket ;

/* Variables and functions */

__attribute__((used)) static void array_bucket_p_sawp(void *p, void *q) /* {{{ */ {
	Bucket *t;
	Bucket **f = (Bucket **)p;
	Bucket **g = (Bucket **)q;

	t = *f;
	*f = *g;
	*g = t;
}