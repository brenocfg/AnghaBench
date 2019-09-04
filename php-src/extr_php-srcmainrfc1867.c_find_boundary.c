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
typedef  int /*<<< orphan*/  multipart_buffer ;

/* Variables and functions */
 char* get_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int find_boundary(multipart_buffer *self, char *boundary)
{
	char *line;

	/* loop through lines */
	while( (line = get_line(self)) )
	{
		/* finished if we found the boundary */
		if (!strcmp(line, boundary)) {
			return 1;
		}
	}

	/* didn't find the boundary */
	return 0;
}