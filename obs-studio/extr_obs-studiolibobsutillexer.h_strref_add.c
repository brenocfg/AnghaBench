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
struct strref {scalar_t__ len; int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  strref_copy (struct strref*,struct strref const*) ; 

__attribute__((used)) static inline void strref_add(struct strref *dst, const struct strref *t)
{
	if (!dst->array)
		strref_copy(dst, t);
	else
		dst->len += t->len;
}