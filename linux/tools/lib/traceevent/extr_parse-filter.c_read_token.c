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
 int TEP_EVENT_ERROR ; 
 int TEP_EVENT_NEWLINE ; 
 int TEP_EVENT_SPACE ; 
 int /*<<< orphan*/  free_token (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char tep_peek_char () ; 
 int tep_read_token (char**) ; 

__attribute__((used)) static enum tep_event_type read_token(char **tok)
{
	enum tep_event_type type;
	char *token = NULL;

	do {
		free_token(token);
		type = tep_read_token(&token);
	} while (type == TEP_EVENT_NEWLINE || type == TEP_EVENT_SPACE);

	/* If token is = or ! check to see if the next char is ~ */
	if (token &&
	    (strcmp(token, "=") == 0 || strcmp(token, "!") == 0) &&
	    tep_peek_char() == '~') {
		/* append it */
		*tok = malloc(3);
		if (*tok == NULL) {
			free_token(token);
			return TEP_EVENT_ERROR;
		}
		sprintf(*tok, "%c%c", *token, '~');
		free_token(token);
		/* Now remove the '~' from the buffer */
		tep_read_token(&token);
		free_token(token);
	} else
		*tok = token;

	return type;
}