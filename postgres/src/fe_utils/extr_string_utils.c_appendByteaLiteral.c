#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; int len; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  enlargePQExpBuffer (TYPE_1__*,int) ; 

void
appendByteaLiteral(PQExpBuffer buf, const unsigned char *str, size_t length,
				   bool std_strings)
{
	const unsigned char *source = str;
	char	   *target;

	static const char hextbl[] = "0123456789abcdef";

	/*
	 * This implementation is hard-wired to produce hex-format output. We do
	 * not know the server version the output will be loaded into, so making
	 * an intelligent format choice is impossible.  It might be better to
	 * always use the old escaped format.
	 */
	if (!enlargePQExpBuffer(buf, 2 * length + 5))
		return;

	target = buf->data + buf->len;
	*target++ = '\'';
	if (!std_strings)
		*target++ = '\\';
	*target++ = '\\';
	*target++ = 'x';

	while (length-- > 0)
	{
		unsigned char c = *source++;

		*target++ = hextbl[(c >> 4) & 0xF];
		*target++ = hextbl[c & 0xF];
	}

	/* Write the terminating quote and NUL character. */
	*target++ = '\'';
	*target = '\0';

	buf->len = target - buf->data;
}