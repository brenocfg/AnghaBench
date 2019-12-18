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
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  pg_free (char*) ; 
 scalar_t__ pg_malloc (int) ; 
 scalar_t__ pg_realloc (char*,int) ; 
 int piperead (int,char*,int) ; 

__attribute__((used)) static char *
readMessageFromPipe(int fd)
{
	char	   *msg;
	int			msgsize,
				bufsize;
	int			ret;

	/*
	 * In theory, if we let piperead() read multiple bytes, it might give us
	 * back fragments of multiple messages.  (That can't actually occur, since
	 * neither master nor workers send more than one message without waiting
	 * for a reply, but we don't wish to assume that here.)  For simplicity,
	 * read a byte at a time until we get the terminating '\0'.  This method
	 * is a bit inefficient, but since this is only used for relatively short
	 * command and status strings, it shouldn't matter.
	 */
	bufsize = 64;				/* could be any number */
	msg = (char *) pg_malloc(bufsize);
	msgsize = 0;
	for (;;)
	{
		Assert(msgsize < bufsize);
		ret = piperead(fd, msg + msgsize, 1);
		if (ret <= 0)
			break;				/* error or connection closure */

		Assert(ret == 1);

		if (msg[msgsize] == '\0')
			return msg;			/* collected whole message */

		msgsize++;
		if (msgsize == bufsize) /* enlarge buffer if needed */
		{
			bufsize += 16;		/* could be any number */
			msg = (char *) pg_realloc(msg, bufsize);
		}
	}

	/* Other end has closed the connection */
	pg_free(msg);
	return NULL;
}