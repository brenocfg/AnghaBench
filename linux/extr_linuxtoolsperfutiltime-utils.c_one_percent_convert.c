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
typedef  int /*<<< orphan*/  u64 ;
struct perf_time_interval {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int percent_slash_split (char*,struct perf_time_interval*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int one_percent_convert(struct perf_time_interval *ptime_buf,
			       const char *ostr, u64 start, u64 end, char *c)
{
	char *str;
	int len = strlen(ostr), ret;

	/*
	 * c points to '%'.
	 * '%' should be the last character
	 */
	if (ostr + len - 1 != c)
		return -1;

	/*
	 * Construct a string like "xx%/1"
	 */
	str = malloc(len + 3);
	if (str == NULL)
		return -ENOMEM;

	memcpy(str, ostr, len);
	strcpy(str + len, "/1");

	ret = percent_slash_split(str, ptime_buf, start, end);
	if (ret == 0)
		ret = 1;

	free(str);
	return ret;
}