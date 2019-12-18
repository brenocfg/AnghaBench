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
typedef  enum tep_event_type { ____Placeholder_tep_event_type } tep_event_type ;

/* Variables and functions */
 int TEP_EVENT_NEWLINE ; 
 int TEP_EVENT_NONE ; 
 int TEP_EVENT_SPACE ; 
 int __read_token (char**) ; 
 int /*<<< orphan*/  free_token (char*) ; 

__attribute__((used)) static enum tep_event_type read_token_item(char **tok)
{
	enum tep_event_type type;

	for (;;) {
		type = __read_token(tok);
		if (type != TEP_EVENT_SPACE && type != TEP_EVENT_NEWLINE)
			return type;
		free_token(*tok);
		*tok = NULL;
	}

	/* not reached */
	*tok = NULL;
	return TEP_EVENT_NONE;
}