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

/* Variables and functions */
 int /*<<< orphan*/  CMDBUFSIZ ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 int read (int /*<<< orphan*/ ,...) ; 
 scalar_t__ realloc (char*,int) ; 
 int /*<<< orphan*/  sd ; 
 int /*<<< orphan*/  workshop_connection_closed () ; 

__attribute__((used)) static char *
getCommand(void)
{
	int	 len;		/* length of this command */
	char	 lenbuf[7];	/* get the length string here */
	char	*newcb;		/* used to realloc cmdbuf */
	static char	*cmdbuf;/* get the command string here */
	static int	 cbsize;/* size of cmdbuf */

	if ((len = read(sd, &lenbuf, 6)) == 6) {
		lenbuf[6] = 0; /* Terminate buffer such that atoi() works right */
		len = atoi(lenbuf);
		if (cbsize < (len + 1)) {
			newcb = (char *) realloc(cmdbuf,
			    MAX((len + 256), CMDBUFSIZ));
			if (newcb != NULL) {
				cmdbuf = newcb;
				cbsize = MAX((len + 256), CMDBUFSIZ);
			}
		}
		if (cbsize >= len && (len = read(sd, cmdbuf, len)) > 0) {
			cmdbuf[len] = 0;
			return cmdbuf;
		} else {
			return NULL;
		}
	} else {
		if (len == 0) { /* EOF */
			workshop_connection_closed();
		}
		return NULL;
	}

}