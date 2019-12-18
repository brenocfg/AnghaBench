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
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 char* strchr (char const*,char) ; 

__attribute__((used)) static int
count_lines_in_buf(PQExpBuffer buf)
{
	int			lineno = 0;
	const char *lines = buf->data;

	while (*lines != '\0')
	{
		lineno++;
		/* find start of next line */
		lines = strchr(lines, '\n');
		if (!lines)
			break;
		lines++;
	}

	return lineno;
}