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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static int parse_dcc(char *data, const char *data_end, __be32 *ip,
		     u_int16_t *port, char **ad_beg_p, char **ad_end_p)
{
	char *tmp;

	/* at least 12: "AAAAAAAA P\1\n" */
	while (*data++ != ' ')
		if (data > data_end - 12)
			return -1;

	/* Make sure we have a newline character within the packet boundaries
	 * because simple_strtoul parses until the first invalid character. */
	for (tmp = data; tmp <= data_end; tmp++)
		if (*tmp == '\n')
			break;
	if (tmp > data_end || *tmp != '\n')
		return -1;

	*ad_beg_p = data;
	*ip = cpu_to_be32(simple_strtoul(data, &data, 10));

	/* skip blanks between ip and port */
	while (*data == ' ') {
		if (data >= data_end)
			return -1;
		data++;
	}

	*port = simple_strtoul(data, &data, 10);
	*ad_end_p = data;

	return 0;
}