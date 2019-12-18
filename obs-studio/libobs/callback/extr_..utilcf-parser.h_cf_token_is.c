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
struct cf_parser {TYPE_1__* cur_token; } ;
struct TYPE_2__ {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ strref_cmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline bool cf_token_is(struct cf_parser *p, const char *val)
{
	return strref_cmp(&p->cur_token->str, val) == 0;
}