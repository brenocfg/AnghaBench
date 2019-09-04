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
 char get_hex_char (char const*,int*) ; 
 char get_oct_char (char const*,int*) ; 

char get_escape_char(const char *s, int *i)
{
	char	c = s[*i];
	int	j = *i + 1;
	char	val;

	switch (c) {
	case 'a':
		val = '\a';
		break;
	case 'b':
		val = '\b';
		break;
	case 't':
		val = '\t';
		break;
	case 'n':
		val = '\n';
		break;
	case 'v':
		val = '\v';
		break;
	case 'f':
		val = '\f';
		break;
	case 'r':
		val = '\r';
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		j--; /* need to re-read the first digit as
		      * part of the octal value */
		val = get_oct_char(s, &j);
		break;
	case 'x':
		val = get_hex_char(s, &j);
		break;
	default:
		val = c;
	}

	(*i) = j;
	return val;
}