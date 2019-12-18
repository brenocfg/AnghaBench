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
struct TYPE_3__ {size_t rm_eo; size_t rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EXTENDED ; 
 int is_full_cpuid (char const*) ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ *,char const*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 char const* strrchr (char const*,char) ; 

int strcmp_cpuid_str(const char *mapcpuid, const char *id)
{
	regex_t re;
	regmatch_t pmatch[1];
	int match;
	bool full_mapcpuid = is_full_cpuid(mapcpuid);
	bool full_cpuid = is_full_cpuid(id);

	/*
	 * Full CPUID format is required to identify a platform.
	 * Error out if the cpuid string is incomplete.
	 */
	if (full_mapcpuid && !full_cpuid) {
		pr_info("Invalid CPUID %s. Full CPUID is required, "
			"vendor-family-model-stepping\n", id);
		return 1;
	}

	if (regcomp(&re, mapcpuid, REG_EXTENDED) != 0) {
		/* Warn unable to generate match particular string. */
		pr_info("Invalid regular expression %s\n", mapcpuid);
		return 1;
	}

	match = !regexec(&re, id, 1, pmatch, 0);
	regfree(&re);
	if (match) {
		size_t match_len = (pmatch[0].rm_eo - pmatch[0].rm_so);
		size_t cpuid_len;

		/* If the full CPUID format isn't required,
		 * ignoring the stepping.
		 */
		if (!full_mapcpuid && full_cpuid)
			cpuid_len = strrchr(id, '-') - id;
		else
			cpuid_len = strlen(id);

		/* Verify the entire string matched. */
		if (match_len == cpuid_len)
			return 0;
	}

	return 1;
}