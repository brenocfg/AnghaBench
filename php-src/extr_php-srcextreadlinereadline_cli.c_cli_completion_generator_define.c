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
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 char* cli_completion_generator_ht (char const*,size_t,int*,int /*<<< orphan*/ *,void**) ; 
 char rl_completion_append_character ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *cli_completion_generator_define(const char *text, size_t textlen, int *state, HashTable *ht) /* {{{ */
{
	zend_class_entry **pce;
	char *retval = cli_completion_generator_ht(text, textlen, state, ht, (void**)&pce);
	if (retval) {
		rl_completion_append_character = '\0';
		retval = strdup(retval);
	}

	return retval;
}