#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_3__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  constants_table; int /*<<< orphan*/  function_table; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/ * EG (int /*<<< orphan*/ ) ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 char* cli_completion_generator_class (char*,size_t,int*) ; 
 char* cli_completion_generator_define (char const*,size_t,int*,int /*<<< orphan*/ *) ; 
 char* cli_completion_generator_func (char*,size_t,int*,int /*<<< orphan*/ *) ; 
 char* cli_completion_generator_ini (char const*,size_t,int*) ; 
 char* cli_completion_generator_var (char const*,size_t,int*) ; 
 int cli_completion_state ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  function_table ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/  zend_constants ; 
 TYPE_1__* zend_lookup_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_str_tolower_copy (char*,char const*,size_t) ; 
 char* zend_str_tolower_dup (char const*,size_t) ; 
 int /*<<< orphan*/ * zend_string_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *cli_completion_generator(const char *text, int index) /* {{{ */
{
/*
TODO:
- constants
- maybe array keys
- language constructs and other things outside a hashtable (echo, try, function, class, ...)
- object/class members

- future: respect scope ("php > function foo() { $[tab]" should only expand to local variables...)
*/
	char *retval = NULL;
	size_t textlen = strlen(text);

	if (!index) {
		cli_completion_state = 0;
	}
	if (text[0] == '$') {
		retval = cli_completion_generator_var(text, textlen, &cli_completion_state);
	} else if (text[0] == '#') {
		retval = cli_completion_generator_ini(text, textlen, &cli_completion_state);
	} else {
		char *lc_text, *class_name_end;
		zend_string *class_name = NULL;
		zend_class_entry *ce = NULL;

		class_name_end = strstr(text, "::");
		if (class_name_end) {
			size_t class_name_len = class_name_end - text;
			class_name = zend_string_alloc(class_name_len, 0);
			zend_str_tolower_copy(ZSTR_VAL(class_name), text, class_name_len);
			if ((ce = zend_lookup_class(class_name)) == NULL) {
				zend_string_release_ex(class_name, 0);
				return NULL;
			}
			lc_text = zend_str_tolower_dup(class_name_end + 2, textlen - 2 - class_name_len);
			textlen -= (class_name_len + 2);
		} else {
			lc_text = zend_str_tolower_dup(text, textlen);
		}

		switch (cli_completion_state) {
			case 0:
			case 1:
				retval = cli_completion_generator_func(lc_text, textlen, &cli_completion_state, ce ? &ce->function_table : EG(function_table));
				if (retval) {
					break;
				}
			case 2:
			case 3:
				retval = cli_completion_generator_define(text, textlen, &cli_completion_state, ce ? &ce->constants_table : EG(zend_constants));
				if (retval || ce) {
					break;
				}
			case 4:
			case 5:
				retval = cli_completion_generator_class(lc_text, textlen, &cli_completion_state);
				break;
			default:
				break;
		}
		efree(lc_text);
		if (class_name) {
			zend_string_release_ex(class_name, 0);
		}
		if (ce && retval) {
			size_t len = ZSTR_LEN(ce->name) + 2 + strlen(retval) + 1;
			char *tmp = malloc(len);

			snprintf(tmp, len, "%s::%s", ZSTR_VAL(ce->name), retval);
			free(retval);
			retval = tmp;
		}
	}

	return retval;
}