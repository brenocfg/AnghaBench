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
 unsigned int ESCAPE_HEX ; 
 unsigned int ESCAPE_NP ; 
 unsigned int ESCAPE_NULL ; 
 unsigned int ESCAPE_OCTAL ; 
 unsigned int ESCAPE_SPACE ; 
 unsigned int ESCAPE_SPECIAL ; 
 scalar_t__ escape_hex (unsigned char,char**,char*) ; 
 scalar_t__ escape_null (unsigned char,char**,char*) ; 
 scalar_t__ escape_octal (unsigned char,char**,char*) ; 
 int /*<<< orphan*/  escape_passthrough (unsigned char,char**,char*) ; 
 scalar_t__ escape_space (unsigned char,char**,char*) ; 
 scalar_t__ escape_special (unsigned char,char**,char*) ; 
 scalar_t__ isprint (unsigned char) ; 
 int /*<<< orphan*/  strchr (char const*,unsigned char) ; 

int string_escape_mem(const char *src, size_t isz, char *dst, size_t osz,
		      unsigned int flags, const char *only)
{
	char *p = dst;
	char *end = p + osz;
	bool is_dict = only && *only;

	while (isz--) {
		unsigned char c = *src++;

		/*
		 * Apply rules in the following sequence:
		 *	- the character is printable, when @flags has
		 *	  %ESCAPE_NP bit set
		 *	- the @only string is supplied and does not contain a
		 *	  character under question
		 *	- the character doesn't fall into a class of symbols
		 *	  defined by given @flags
		 * In these cases we just pass through a character to the
		 * output buffer.
		 */
		if ((flags & ESCAPE_NP && isprint(c)) ||
		    (is_dict && !strchr(only, c))) {
			/* do nothing */
		} else {
			if (flags & ESCAPE_SPACE && escape_space(c, &p, end))
				continue;

			if (flags & ESCAPE_SPECIAL && escape_special(c, &p, end))
				continue;

			if (flags & ESCAPE_NULL && escape_null(c, &p, end))
				continue;

			/* ESCAPE_OCTAL and ESCAPE_HEX always go last */
			if (flags & ESCAPE_OCTAL && escape_octal(c, &p, end))
				continue;

			if (flags & ESCAPE_HEX && escape_hex(c, &p, end))
				continue;
		}

		escape_passthrough(c, &p, end);
	}

	return p - dst;
}