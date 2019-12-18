#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int histcontrol; } ;
struct TYPE_5__ {char* data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  add_history (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hctl_ignoredups ; 
 int hctl_ignorespace ; 
 int /*<<< orphan*/  history_lines_added ; 
 char* pg_strdup (char*) ; 
 TYPE_3__ pset ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ useHistory ; 

void
pg_send_history(PQExpBuffer history_buf)
{
#ifdef USE_READLINE
	static char *prev_hist = NULL;

	char	   *s = history_buf->data;
	int			i;

	/* Trim any trailing \n's (OK to scribble on history_buf) */
	for (i = strlen(s) - 1; i >= 0 && s[i] == '\n'; i--)
		;
	s[i + 1] = '\0';

	if (useHistory && s[0])
	{
		if (((pset.histcontrol & hctl_ignorespace) &&
			 s[0] == ' ') ||
			((pset.histcontrol & hctl_ignoredups) &&
			 prev_hist && strcmp(s, prev_hist) == 0))
		{
			/* Ignore this line as far as history is concerned */
		}
		else
		{
			/* Save each previous line for ignoredups processing */
			if (prev_hist)
				free(prev_hist);
			prev_hist = pg_strdup(s);
			/* And send it to readline */
			add_history(s);
			/* Count lines added to history for use later */
			history_lines_added++;
		}
	}

	resetPQExpBuffer(history_buf);
#endif
}