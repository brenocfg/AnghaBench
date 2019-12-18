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
 int /*<<< orphan*/  IDENTIFIER_LOOKUP_NORMAL ; 
 int /*<<< orphan*/  ReservedPLKeywordTokens ; 
 int /*<<< orphan*/  ReservedPLKeywords ; 
 int /*<<< orphan*/  core_yy ; 
 int /*<<< orphan*/  location_lineno_init () ; 
 scalar_t__ num_pushbacks ; 
 int /*<<< orphan*/  plpgsql_IdentifierLookup ; 
 scalar_t__ plpgsql_yytoken ; 
 int /*<<< orphan*/  scanner_init (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* scanorig ; 
 int /*<<< orphan*/  yyscanner ; 

void
plpgsql_scanner_init(const char *str)
{
	/* Start up the core scanner */
	yyscanner = scanner_init(str, &core_yy,
							 &ReservedPLKeywords, ReservedPLKeywordTokens);

	/*
	 * scanorig points to the original string, which unlike the scanner's
	 * scanbuf won't be modified on-the-fly by flex.  Notice that although
	 * yytext points into scanbuf, we rely on being able to apply locations
	 * (offsets from string start) to scanorig as well.
	 */
	scanorig = str;

	/* Other setup */
	plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
	plpgsql_yytoken = 0;

	num_pushbacks = 0;

	location_lineno_init();
}