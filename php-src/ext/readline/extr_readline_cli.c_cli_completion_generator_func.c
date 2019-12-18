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
struct TYPE_3__ {int /*<<< orphan*/  function_name; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
typedef  TYPE_2__ zend_function ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 char* cli_completion_generator_ht (char const*,size_t,int*,int /*<<< orphan*/ *,void**) ; 
 char rl_completion_append_character ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *cli_completion_generator_func(const char *text, size_t textlen, int *state, HashTable *ht) /* {{{ */
{
	zend_function *func;
	char *retval = cli_completion_generator_ht(text, textlen, state, ht, (void**)&func);
	if (retval) {
		rl_completion_append_character = '(';
		retval = strdup(ZSTR_VAL(func->common.function_name));
	}

	return retval;
}