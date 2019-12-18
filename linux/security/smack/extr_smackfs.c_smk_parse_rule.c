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

/* Variables and functions */
 int SMK_LABELLEN ; 
 int smk_fill_rule (char const*,char const*,char const*,int /*<<< orphan*/ *,struct smack_parsed_rule*,int,int) ; 

__attribute__((used)) static int smk_parse_rule(const char *data, struct smack_parsed_rule *rule,
				int import)
{
	int rc;

	rc = smk_fill_rule(data, data + SMK_LABELLEN,
			   data + SMK_LABELLEN + SMK_LABELLEN, NULL, rule,
			   import, SMK_LABELLEN);
	return rc;
}