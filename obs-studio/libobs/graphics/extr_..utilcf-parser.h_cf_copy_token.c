#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cf_parser {TYPE_2__* cur_token; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;
struct TYPE_4__ {TYPE_1__ str; } ;

/* Variables and functions */
 char* bstrdup_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cf_copy_token(struct cf_parser *p, char **dst)
{
	*dst = bstrdup_n(p->cur_token->str.array, p->cur_token->str.len);
}