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
struct prepared_statement {int /*<<< orphan*/  name; struct prepared_statement* next; } ;
struct connection {struct prepared_statement* prep_stmts; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct prepared_statement *
ecpg_find_prepared_statement(const char *name,
							 struct connection *con, struct prepared_statement **prev_)
{
	struct prepared_statement *this,
			   *prev;

	for (this = con->prep_stmts, prev = NULL;
		 this != NULL;
		 prev = this, this = this->next)
	{
		if (strcmp(this->name, name) == 0)
		{
			if (prev_)
				*prev_ = prev;
			return this;
		}
	}
	return NULL;
}