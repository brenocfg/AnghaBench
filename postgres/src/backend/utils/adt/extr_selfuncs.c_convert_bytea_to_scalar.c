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
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetByteaPP (int /*<<< orphan*/ ) ; 
 int Min (int,int) ; 
 scalar_t__ VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 double convert_one_bytea_to_scalar (unsigned char*,int,int,int) ; 

__attribute__((used)) static void
convert_bytea_to_scalar(Datum value,
						double *scaledvalue,
						Datum lobound,
						double *scaledlobound,
						Datum hibound,
						double *scaledhibound)
{
	bytea	   *valuep = DatumGetByteaPP(value);
	bytea	   *loboundp = DatumGetByteaPP(lobound);
	bytea	   *hiboundp = DatumGetByteaPP(hibound);
	int			rangelo,
				rangehi,
				valuelen = VARSIZE_ANY_EXHDR(valuep),
				loboundlen = VARSIZE_ANY_EXHDR(loboundp),
				hiboundlen = VARSIZE_ANY_EXHDR(hiboundp),
				i,
				minlen;
	unsigned char *valstr = (unsigned char *) VARDATA_ANY(valuep);
	unsigned char *lostr = (unsigned char *) VARDATA_ANY(loboundp);
	unsigned char *histr = (unsigned char *) VARDATA_ANY(hiboundp);

	/*
	 * Assume bytea data is uniformly distributed across all byte values.
	 */
	rangelo = 0;
	rangehi = 255;

	/*
	 * Now strip any common prefix of the three strings.
	 */
	minlen = Min(Min(valuelen, loboundlen), hiboundlen);
	for (i = 0; i < minlen; i++)
	{
		if (*lostr != *histr || *lostr != *valstr)
			break;
		lostr++, histr++, valstr++;
		loboundlen--, hiboundlen--, valuelen--;
	}

	/*
	 * Now we can do the conversions.
	 */
	*scaledvalue = convert_one_bytea_to_scalar(valstr, valuelen, rangelo, rangehi);
	*scaledlobound = convert_one_bytea_to_scalar(lostr, loboundlen, rangelo, rangehi);
	*scaledhibound = convert_one_bytea_to_scalar(histr, hiboundlen, rangelo, rangehi);
}