#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
struct TYPE_6__ {int len; char* data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ PQExpBufferBroken (TYPE_1__*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 char* pg_strdup (char*) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 
 int sigint_interrupt_enabled ; 

char *
gets_fromFile(FILE *source)
{
	static PQExpBuffer buffer = NULL;

	char		line[1024];

	if (buffer == NULL)			/* first time through? */
		buffer = createPQExpBuffer();
	else
		resetPQExpBuffer(buffer);

	for (;;)
	{
		char	   *result;

		/* Enable SIGINT to longjmp to sigint_interrupt_jmp */
		sigint_interrupt_enabled = true;

		/* Get some data */
		result = fgets(line, sizeof(line), source);

		/* Disable SIGINT again */
		sigint_interrupt_enabled = false;

		/* EOF or error? */
		if (result == NULL)
		{
			if (ferror(source))
			{
				pg_log_error("could not read from input file: %m");
				return NULL;
			}
			break;
		}

		appendPQExpBufferStr(buffer, line);

		if (PQExpBufferBroken(buffer))
		{
			pg_log_error("out of memory");
			return NULL;
		}

		/* EOL? */
		if (buffer->len > 0 && buffer->data[buffer->len - 1] == '\n')
		{
			buffer->data[buffer->len - 1] = '\0';
			return pg_strdup(buffer->data);
		}
	}

	if (buffer->len > 0)		/* EOF after reading some bufferload(s) */
		return pg_strdup(buffer->data);

	/* EOF, so return null */
	return NULL;
}