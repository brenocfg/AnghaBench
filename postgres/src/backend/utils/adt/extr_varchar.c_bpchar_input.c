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
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  BpChar ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_STRING_DATA_RIGHT_TRUNCATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 char* VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 scalar_t__ palloc (scalar_t__) ; 
 size_t pg_mbcharcliplen (char const*,size_t,size_t) ; 
 size_t pg_mbstrlen_with_len (char const*,size_t) ; 

__attribute__((used)) static BpChar *
bpchar_input(const char *s, size_t len, int32 atttypmod)
{
	BpChar	   *result;
	char	   *r;
	size_t		maxlen;

	/* If typmod is -1 (or invalid), use the actual string length */
	if (atttypmod < (int32) VARHDRSZ)
		maxlen = len;
	else
	{
		size_t		charlen;	/* number of CHARACTERS in the input */

		maxlen = atttypmod - VARHDRSZ;
		charlen = pg_mbstrlen_with_len(s, len);
		if (charlen > maxlen)
		{
			/* Verify that extra characters are spaces, and clip them off */
			size_t		mbmaxlen = pg_mbcharcliplen(s, len, maxlen);
			size_t		j;

			/*
			 * at this point, len is the actual BYTE length of the input
			 * string, maxlen is the max number of CHARACTERS allowed for this
			 * bpchar type, mbmaxlen is the length in BYTES of those chars.
			 */
			for (j = mbmaxlen; j < len; j++)
			{
				if (s[j] != ' ')
					ereport(ERROR,
							(errcode(ERRCODE_STRING_DATA_RIGHT_TRUNCATION),
							 errmsg("value too long for type character(%d)",
									(int) maxlen)));
			}

			/*
			 * Now we set maxlen to the necessary byte length, not the number
			 * of CHARACTERS!
			 */
			maxlen = len = mbmaxlen;
		}
		else
		{
			/*
			 * Now we set maxlen to the necessary byte length, not the number
			 * of CHARACTERS!
			 */
			maxlen = len + (maxlen - charlen);
		}
	}

	result = (BpChar *) palloc(maxlen + VARHDRSZ);
	SET_VARSIZE(result, maxlen + VARHDRSZ);
	r = VARDATA(result);
	memcpy(r, s, len);

	/* blank pad the string if necessary */
	if (maxlen > len)
		memset(r + len, ' ', maxlen - len);

	return result;
}