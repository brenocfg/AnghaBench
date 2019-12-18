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
struct TYPE_3__ {unsigned char* data; } ;
typedef  TYPE_1__ pg_uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 int UUID_LEN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char const*) ; 
 int /*<<< orphan*/  isxdigit (unsigned char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
string_to_uuid(const char *source, pg_uuid_t *uuid)
{
	const char *src = source;
	bool		braces = false;
	int			i;

	if (src[0] == '{')
	{
		src++;
		braces = true;
	}

	for (i = 0; i < UUID_LEN; i++)
	{
		char		str_buf[3];

		if (src[0] == '\0' || src[1] == '\0')
			goto syntax_error;
		memcpy(str_buf, src, 2);
		if (!isxdigit((unsigned char) str_buf[0]) ||
			!isxdigit((unsigned char) str_buf[1]))
			goto syntax_error;

		str_buf[2] = '\0';
		uuid->data[i] = (unsigned char) strtoul(str_buf, NULL, 16);
		src += 2;
		if (src[0] == '-' && (i % 2) == 1 && i < UUID_LEN - 1)
			src++;
	}

	if (braces)
	{
		if (*src != '}')
			goto syntax_error;
		src++;
	}

	if (*src != '\0')
		goto syntax_error;

	return;

syntax_error:
	ereport(ERROR,
			(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
			 errmsg("invalid input syntax for type %s: \"%s\"",
					"uuid", source)));
}