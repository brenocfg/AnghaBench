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
 void** hextbl ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char *
PQescapeByteaInternal(PGconn *conn,
					  const unsigned char *from, size_t from_length,
					  size_t *to_length, bool std_strings, bool use_hex)
{
	const unsigned char *vp;
	unsigned char *rp;
	unsigned char *result;
	size_t		i;
	size_t		len;
	size_t		bslash_len = (std_strings ? 1 : 2);

	/*
	 * empty string has 1 char ('\0')
	 */
	len = 1;

	if (use_hex)
	{
		len += bslash_len + 1 + 2 * from_length;
	}
	else
	{
		vp = from;
		for (i = from_length; i > 0; i--, vp++)
		{
			if (*vp < 0x20 || *vp > 0x7e)
				len += bslash_len + 3;
			else if (*vp == '\'')
				len += 2;
			else if (*vp == '\\')
				len += bslash_len + bslash_len;
			else
				len++;
		}
	}

	*to_length = len;
	rp = result = (unsigned char *) malloc(len);
	if (rp == NULL)
	{
		if (conn)
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("out of memory\n"));
		return NULL;
	}

	if (use_hex)
	{
		if (!std_strings)
			*rp++ = '\\';
		*rp++ = '\\';
		*rp++ = 'x';
	}

	vp = from;
	for (i = from_length; i > 0; i--, vp++)
	{
		unsigned char c = *vp;

		if (use_hex)
		{
			*rp++ = hextbl[(c >> 4) & 0xF];
			*rp++ = hextbl[c & 0xF];
		}
		else if (c < 0x20 || c > 0x7e)
		{
			if (!std_strings)
				*rp++ = '\\';
			*rp++ = '\\';
			*rp++ = (c >> 6) + '0';
			*rp++ = ((c >> 3) & 07) + '0';
			*rp++ = (c & 07) + '0';
		}
		else if (c == '\'')
		{
			*rp++ = '\'';
			*rp++ = '\'';
		}
		else if (c == '\\')
		{
			if (!std_strings)
			{
				*rp++ = '\\';
				*rp++ = '\\';
			}
			*rp++ = '\\';
			*rp++ = '\\';
		}
		else
			*rp++ = c;
	}
	*rp = '\0';

	return result;
}