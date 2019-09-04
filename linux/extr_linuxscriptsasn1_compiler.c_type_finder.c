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
struct type {TYPE_1__* name; } ;
struct token {scalar_t__ size; int /*<<< orphan*/  content; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  content; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int type_finder(const void *_key, const void *_ti)
{
	const struct token *token = _key;
	const struct type *const *ti = _ti;
	const struct type *type = *ti;

	if (token->size != type->name->size)
		return token->size - type->name->size;
	else
		return memcmp(token->content, type->name->content,
			      token->size);
}