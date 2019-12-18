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
struct TYPE_3__ {int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ errno ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static bool
parse_int_param(const char *value, int *result, PGconn *conn,
				const char *context)
{
	char	   *end;
	long		numval;

	Assert(value != NULL);

	*result = 0;

	/* strtol(3) skips leading whitespaces */
	errno = 0;
	numval = strtol(value, &end, 10);

	/*
	 * If no progress was done during the parsing or an error happened, fail.
	 * This tests properly for overflows of the result.
	 */
	if (value == end || errno != 0 || numval != (int) numval)
		goto error;

	/*
	 * Skip any trailing whitespace; if anything but whitespace remains before
	 * the terminating character, fail
	 */
	while (*end != '\0' && isspace((unsigned char) *end))
		end++;

	if (*end != '\0')
		goto error;

	*result = numval;
	return true;

error:
	appendPQExpBuffer(&conn->errorMessage,
					  libpq_gettext("invalid integer value \"%s\" for connection option \"%s\"\n"),
					  value, context);
	return false;
}