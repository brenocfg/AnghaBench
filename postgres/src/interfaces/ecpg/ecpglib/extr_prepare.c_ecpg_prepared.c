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
struct prepared_statement {TYPE_1__* stmt; } ;
struct connection {int dummy; } ;
struct TYPE_2__ {char* command; } ;

/* Variables and functions */
 struct prepared_statement* ecpg_find_prepared_statement (char const*,struct connection*,int /*<<< orphan*/ *) ; 

char *
ecpg_prepared(const char *name, struct connection *con)
{
	struct prepared_statement *this;

	this = ecpg_find_prepared_statement(name, con, NULL);
	return this ? this->stmt->command : NULL;
}