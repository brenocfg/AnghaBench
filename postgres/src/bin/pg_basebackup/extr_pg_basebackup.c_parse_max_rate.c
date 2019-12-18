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
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 double MAX_RATE_LOWER ; 
 double MAX_RATE_UPPER ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 double strtod (char*,char**) ; 

__attribute__((used)) static int32
parse_max_rate(char *src)
{
	double		result;
	char	   *after_num;
	char	   *suffix = NULL;

	errno = 0;
	result = strtod(src, &after_num);
	if (src == after_num)
	{
		pg_log_error("transfer rate \"%s\" is not a valid value", src);
		exit(1);
	}
	if (errno != 0)
	{
		pg_log_error("invalid transfer rate \"%s\": %m", src);
		exit(1);
	}

	if (result <= 0)
	{
		/*
		 * Reject obviously wrong values here.
		 */
		pg_log_error("transfer rate must be greater than zero");
		exit(1);
	}

	/*
	 * Evaluate suffix, after skipping over possible whitespace. Lack of
	 * suffix means kilobytes.
	 */
	while (*after_num != '\0' && isspace((unsigned char) *after_num))
		after_num++;

	if (*after_num != '\0')
	{
		suffix = after_num;
		if (*after_num == 'k')
		{
			/* kilobyte is the expected unit. */
			after_num++;
		}
		else if (*after_num == 'M')
		{
			after_num++;
			result *= 1024.0;
		}
	}

	/* The rest can only consist of white space. */
	while (*after_num != '\0' && isspace((unsigned char) *after_num))
		after_num++;

	if (*after_num != '\0')
	{
		pg_log_error("invalid --max-rate unit: \"%s\"", suffix);
		exit(1);
	}

	/* Valid integer? */
	if ((uint64) result != (uint64) ((uint32) result))
	{
		pg_log_error("transfer rate \"%s\" exceeds integer range", src);
		exit(1);
	}

	/*
	 * The range is checked on the server side too, but avoid the server
	 * connection if a nonsensical value was passed.
	 */
	if (result < MAX_RATE_LOWER || result > MAX_RATE_UPPER)
	{
		pg_log_error("transfer rate \"%s\" is out of range", src);
		exit(1);
	}

	return (int32) result;
}