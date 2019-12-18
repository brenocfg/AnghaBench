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
 int /*<<< orphan*/  isdigit (char const) ; 
 scalar_t__ strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void cf_convert_from_escape_literal(char **p_dst,
						  const char **p_src)
{
	char *dst = *p_dst;
	const char *src = *p_src;

	switch (*(src++)) {
	case '\'':
		*(dst++) = '\'';
		break;
	case '\"':
		*(dst++) = '\"';
		break;
	case '\?':
		*(dst++) = '\?';
		break;
	case '\\':
		*(dst++) = '\\';
		break;
	case '0':
		*(dst++) = '\0';
		break;
	case 'a':
		*(dst++) = '\a';
		break;
	case 'b':
		*(dst++) = '\b';
		break;
	case 'f':
		*(dst++) = '\f';
		break;
	case 'n':
		*(dst++) = '\n';
		break;
	case 'r':
		*(dst++) = '\r';
		break;
	case 't':
		*(dst++) = '\t';
		break;
	case 'v':
		*(dst++) = '\v';
		break;

	/* hex */
	case 'X':
	case 'x':
		*(dst++) = (char)strtoul(src, NULL, 16);
		src += 2;
		break;

	/* oct */
	default:
		if (isdigit(*src)) {
			*(dst++) = (char)strtoul(src, NULL, 8);
			src += 3;
		}

		/* case 'u':
		case 'U': */
	}

	*p_dst = dst;
	*p_src = src;
}