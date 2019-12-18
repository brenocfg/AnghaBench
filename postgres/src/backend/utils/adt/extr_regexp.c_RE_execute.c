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
typedef  int /*<<< orphan*/  regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  pg_wchar ;

/* Variables and functions */
 int RE_wchar_execute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int pg_mb2wchar_with_len (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
RE_execute(regex_t *re, char *dat, int dat_len,
		   int nmatch, regmatch_t *pmatch)
{
	pg_wchar   *data;
	int			data_len;
	bool		match;

	/* Convert data string to wide characters */
	data = (pg_wchar *) palloc((dat_len + 1) * sizeof(pg_wchar));
	data_len = pg_mb2wchar_with_len(dat, data, dat_len);

	/* Perform RE match and return result */
	match = RE_wchar_execute(re, data, data_len, 0, nmatch, pmatch);

	pfree(data);
	return match;
}