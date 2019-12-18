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
struct TYPE_3__ {int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_1__ trgm_mb_char ;
typedef  int /*<<< orphan*/  trgm ;

/* Variables and functions */
 int MAX_MULTIBYTE_CHAR_LEN ; 
 int /*<<< orphan*/  compact_trigram (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
fillTrgm(trgm *ptrgm, trgm_mb_char s[3])
{
	char		str[3 * MAX_MULTIBYTE_CHAR_LEN],
			   *p;
	int			i,
				j;

	/* Write multibyte string into "str" (we don't need null termination) */
	p = str;

	for (i = 0; i < 3; i++)
	{
		if (s[i].bytes[0] != 0)
		{
			for (j = 0; j < MAX_MULTIBYTE_CHAR_LEN && s[i].bytes[j]; j++)
				*p++ = s[i].bytes[j];
		}
		else
		{
			/* Emit a space in place of COLOR_BLANK */
			*p++ = ' ';
		}
	}

	/* Convert "str" to a standard trigram (possibly hashing it) */
	compact_trigram(ptrgm, str, p - str);
}