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
struct cf_token {int /*<<< orphan*/  unmerged_str; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  strref_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cf_token_add(struct cf_token *dst,
				const struct cf_token *add)
{
	strref_add(&dst->str, &add->str);
	strref_add(&dst->unmerged_str, &add->unmerged_str);
}