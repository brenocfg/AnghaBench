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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int SMK_LONGLABEL ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

char *smk_parse_smack(const char *string, int len)
{
	char *smack;
	int i;

	if (len <= 0)
		len = strlen(string) + 1;

	/*
	 * Reserve a leading '-' as an indicator that
	 * this isn't a label, but an option to interfaces
	 * including /smack/cipso and /smack/cipso2
	 */
	if (string[0] == '-')
		return ERR_PTR(-EINVAL);

	for (i = 0; i < len; i++)
		if (string[i] > '~' || string[i] <= ' ' || string[i] == '/' ||
		    string[i] == '"' || string[i] == '\\' || string[i] == '\'')
			break;

	if (i == 0 || i >= SMK_LONGLABEL)
		return ERR_PTR(-EINVAL);

	smack = kzalloc(i + 1, GFP_NOFS);
	if (smack == NULL)
		return ERR_PTR(-ENOMEM);

	strncpy(smack, string, i);

	return smack;
}