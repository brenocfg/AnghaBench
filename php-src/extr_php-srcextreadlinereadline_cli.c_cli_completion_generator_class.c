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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_table ; 
 char* cli_completion_generator_ht (char const*,size_t,int*,int /*<<< orphan*/ ,void**) ; 
 char rl_completion_append_character ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *cli_completion_generator_class(const char *text, size_t textlen, int *state) /* {{{ */
{
	zend_class_entry *ce;
	char *retval = cli_completion_generator_ht(text, textlen, state, EG(class_table), (void**)&ce);
	if (retval) {
		rl_completion_append_character = '\0';
		retval = strdup(ZSTR_VAL(ce->name));
	}

	return retval;
}