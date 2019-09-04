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
struct strref {int /*<<< orphan*/ * array; int /*<<< orphan*/  len; } ;

/* Variables and functions */

__attribute__((used)) static inline bool strref_is_empty(const struct strref *str)
{
	return !str || !str->array || !str->len || !*str->array;
}