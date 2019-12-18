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
typedef  scalar_t__ (* readfn_t ) (void*,unsigned long,char*) ;
typedef  int /*<<< orphan*/  GETS_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int GETS_FETCH_SIZE ; 
 scalar_t__ IMAPG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gets_stream ; 
 char* pemalloc (unsigned long,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 unsigned long php_stream_write (scalar_t__,char*,unsigned long) ; 

__attribute__((used)) static char *php_mail_gets(readfn_t f, void *stream, unsigned long size, GETS_DATA *md) /* {{{ */
{

	/*	write to the gets stream if it is set,
		otherwise forward to c-clients gets */
	if (IMAPG(gets_stream)) {
		char buf[GETS_FETCH_SIZE];

		while (size) {
			unsigned long read;

			if (size > GETS_FETCH_SIZE) {
				read = GETS_FETCH_SIZE;
				size -=GETS_FETCH_SIZE;
			} else {
				read = size;
				size = 0;
			}

			if (!f(stream, read, buf)) {
				php_error_docref(NULL, E_WARNING, "Failed to read from socket");
				break;
			} else if (read != php_stream_write(IMAPG(gets_stream), buf, read)) {
				php_error_docref(NULL, E_WARNING, "Failed to write to stream");
				break;
			}
		}
		return NULL;
	} else {
		char *buf = pemalloc(size + 1, 1);

		if (f(stream, size, buf)) {
			buf[size] = '\0';
		} else {
			php_error_docref(NULL, E_WARNING, "Failed to read from socket");
			free(buf);
			buf = NULL;
		}
		return buf;
	}
}