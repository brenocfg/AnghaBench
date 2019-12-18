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
 int* ECPGScanKeywordTokens ; 
 int* SQLScanKeywordTokens ; 
 int /*<<< orphan*/  ScanECPGKeywords ; 
 int ScanKeywordLookup (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScanKeywords ; 

int
ScanECPGKeywordLookup(const char *text)
{
	int			kwnum;

	/* First check SQL symbols defined by the backend. */
	kwnum = ScanKeywordLookup(text, &ScanKeywords);
	if (kwnum >= 0)
		return SQLScanKeywordTokens[kwnum];

	/* Try ECPG-specific keywords. */
	kwnum = ScanKeywordLookup(text, &ScanECPGKeywords);
	if (kwnum >= 0)
		return ECPGScanKeywordTokens[kwnum];

	return -1;
}