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
struct trace_event_call {char* print_fmt; } ;
struct trace_eval_map {int /*<<< orphan*/  eval_string; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 char* eval_replace (char*,struct trace_eval_map*,int) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (char) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void update_event_printk(struct trace_event_call *call,
				struct trace_eval_map *map)
{
	char *ptr;
	int quote = 0;
	int len = strlen(map->eval_string);

	for (ptr = call->print_fmt; *ptr; ptr++) {
		if (*ptr == '\\') {
			ptr++;
			/* paranoid */
			if (!*ptr)
				break;
			continue;
		}
		if (*ptr == '"') {
			quote ^= 1;
			continue;
		}
		if (quote)
			continue;
		if (isdigit(*ptr)) {
			/* skip numbers */
			do {
				ptr++;
				/* Check for alpha chars like ULL */
			} while (isalnum(*ptr));
			if (!*ptr)
				break;
			/*
			 * A number must have some kind of delimiter after
			 * it, and we can ignore that too.
			 */
			continue;
		}
		if (isalpha(*ptr) || *ptr == '_') {
			if (strncmp(map->eval_string, ptr, len) == 0 &&
			    !isalnum(ptr[len]) && ptr[len] != '_') {
				ptr = eval_replace(ptr, map, len);
				/* enum/sizeof string smaller than value */
				if (WARN_ON_ONCE(!ptr))
					return;
				/*
				 * No need to decrement here, as eval_replace()
				 * returns the pointer to the character passed
				 * the eval, and two evals can not be placed
				 * back to back without something in between.
				 * We can skip that something in between.
				 */
				continue;
			}
		skip_more:
			do {
				ptr++;
			} while (isalnum(*ptr) || *ptr == '_');
			if (!*ptr)
				break;
			/*
			 * If what comes after this variable is a '.' or
			 * '->' then we can continue to ignore that string.
			 */
			if (*ptr == '.' || (ptr[0] == '-' && ptr[1] == '>')) {
				ptr += *ptr == '.' ? 1 : 2;
				if (!*ptr)
					break;
				goto skip_more;
			}
			/*
			 * Once again, we can skip the delimiter that came
			 * after the string.
			 */
			continue;
		}
	}
}