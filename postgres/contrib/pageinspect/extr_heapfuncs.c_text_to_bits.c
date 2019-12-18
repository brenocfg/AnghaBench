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
typedef  char bits8 ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char) ; 
 char* palloc (int) ; 

__attribute__((used)) static bits8 *
text_to_bits(char *str, int len)
{
	bits8	   *bits;
	int			off = 0;
	char		byte = 0;

	bits = palloc(len + 1);

	while (off < len)
	{
		if (off % 8 == 0)
			byte = 0;

		if ((str[off] == '0') || (str[off] == '1'))
			byte = byte | ((str[off] - '0') << off % 8);
		else
			ereport(ERROR,
					(errcode(ERRCODE_DATA_CORRUPTED),
					 errmsg("illegal character '%c' in t_bits string", str[off])));

		if (off % 8 == 7)
			bits[off / 8] = byte;

		off++;
	}

	return bits;
}