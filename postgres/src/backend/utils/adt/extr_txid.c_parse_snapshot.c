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
typedef  scalar_t__ txid ;
typedef  int /*<<< orphan*/  TxidSnapshot ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  buf_add_txid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * buf_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_init (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char const*) ; 
 scalar_t__ str2txid (char const*,char const**) ; 

__attribute__((used)) static TxidSnapshot *
parse_snapshot(const char *str)
{
	txid		xmin;
	txid		xmax;
	txid		last_val = 0,
				val;
	const char *str_start = str;
	const char *endp;
	StringInfo	buf;

	xmin = str2txid(str, &endp);
	if (*endp != ':')
		goto bad_format;
	str = endp + 1;

	xmax = str2txid(str, &endp);
	if (*endp != ':')
		goto bad_format;
	str = endp + 1;

	/* it should look sane */
	if (xmin == 0 || xmax == 0 || xmin > xmax)
		goto bad_format;

	/* allocate buffer */
	buf = buf_init(xmin, xmax);

	/* loop over values */
	while (*str != '\0')
	{
		/* read next value */
		val = str2txid(str, &endp);
		str = endp;

		/* require the input to be in order */
		if (val < xmin || val >= xmax || val < last_val)
			goto bad_format;

		/* skip duplicates */
		if (val != last_val)
			buf_add_txid(buf, val);
		last_val = val;

		if (*str == ',')
			str++;
		else if (*str != '\0')
			goto bad_format;
	}

	return buf_finalize(buf);

bad_format:
	ereport(ERROR,
			(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
			 errmsg("invalid input syntax for type %s: \"%s\"",
					"txid_snapshot", str_start)));
	return NULL;				/* keep compiler quiet */
}