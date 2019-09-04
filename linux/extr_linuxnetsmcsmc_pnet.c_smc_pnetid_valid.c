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
 int SMC_MAX_PNETID_LEN ; 
 int /*<<< orphan*/  isalnum (char) ; 
 scalar_t__ islower (char) ; 
 scalar_t__ isspace (char) ; 
 char* skip_spaces (char const*) ; 
 size_t strlen (char*) ; 
 char toupper (char) ; 

__attribute__((used)) static bool smc_pnetid_valid(const char *pnet_name, char *pnetid)
{
	char *bf = skip_spaces(pnet_name);
	size_t len = strlen(bf);
	char *end = bf + len;

	if (!len)
		return false;
	while (--end >= bf && isspace(*end))
		;
	if (end - bf >= SMC_MAX_PNETID_LEN)
		return false;
	while (bf <= end) {
		if (!isalnum(*bf))
			return false;
		*pnetid++ = islower(*bf) ? toupper(*bf) : *bf;
		bf++;
	}
	*pnetid = '\0';
	return true;
}