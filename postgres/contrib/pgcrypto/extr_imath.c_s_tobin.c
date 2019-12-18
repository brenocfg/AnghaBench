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
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/  mp_int ;
typedef  int mp_digit ;

/* Variables and functions */
 int CHAR_BIT ; 
 int* MP_DIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_TRUNC ; 
 int MP_USED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REV (unsigned char*,int) ; 

__attribute__((used)) static mp_result
s_tobin(mp_int z, unsigned char *buf, int *limpos, int pad)
{
	int			pos = 0,
				limit = *limpos;
	mp_size		uz = MP_USED(z);
	mp_digit   *dz = MP_DIGITS(z);

	while (uz > 0 && pos < limit)
	{
		mp_digit	d = *dz++;
		int			i;

		for (i = sizeof(mp_digit); i > 0 && pos < limit; --i)
		{
			buf[pos++] = (unsigned char) d;
			d >>= CHAR_BIT;

			/* Don't write leading zeroes */
			if (d == 0 && uz == 1)
				i = 0;			/* exit loop without signaling truncation */
		}

		/* Detect truncation (loop exited with pos >= limit) */
		if (i > 0)
			break;

		--uz;
	}

	if (pad != 0 && (buf[pos - 1] >> (CHAR_BIT - 1)))
	{
		if (pos < limit)
		{
			buf[pos++] = 0;
		}
		else
		{
			uz = 1;
		}
	}

	/* Digits are in reverse order, fix that */
	REV(buf, pos);

	/* Return the number of bytes actually written */
	*limpos = pos;

	return (uz == 0) ? MP_OK : MP_TRUNC;
}