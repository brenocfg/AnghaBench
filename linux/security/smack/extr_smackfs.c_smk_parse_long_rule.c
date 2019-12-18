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
struct smack_parsed_rule {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ isspace (char) ; 
 int smk_fill_rule (char*,char*,char*,char*,struct smack_parsed_rule*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t smk_parse_long_rule(char *data, struct smack_parsed_rule *rule,
				int import, int tokens)
{
	ssize_t cnt = 0;
	char *tok[4];
	int rc;
	int i;

	/*
	 * Parsing the rule in-place, filling all white-spaces with '\0'
	 */
	for (i = 0; i < tokens; ++i) {
		while (isspace(data[cnt]))
			data[cnt++] = '\0';

		if (data[cnt] == '\0')
			/* Unexpected end of data */
			return -EINVAL;

		tok[i] = data + cnt;

		while (data[cnt] && !isspace(data[cnt]))
			++cnt;
	}
	while (isspace(data[cnt]))
		data[cnt++] = '\0';

	while (i < 4)
		tok[i++] = NULL;

	rc = smk_fill_rule(tok[0], tok[1], tok[2], tok[3], rule, import, 0);
	return rc == 0 ? cnt : rc;
}