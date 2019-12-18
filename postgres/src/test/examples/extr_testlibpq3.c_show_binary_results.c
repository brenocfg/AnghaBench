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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int PQgetlength (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
show_binary_results(PGresult *res)
{
	int			i,
				j;
	int			i_fnum,
				t_fnum,
				b_fnum;

	/* Use PQfnumber to avoid assumptions about field order in result */
	i_fnum = PQfnumber(res, "i");
	t_fnum = PQfnumber(res, "t");
	b_fnum = PQfnumber(res, "b");

	for (i = 0; i < PQntuples(res); i++)
	{
		char	   *iptr;
		char	   *tptr;
		char	   *bptr;
		int			blen;
		int			ival;

		/* Get the field values (we ignore possibility they are null!) */
		iptr = PQgetvalue(res, i, i_fnum);
		tptr = PQgetvalue(res, i, t_fnum);
		bptr = PQgetvalue(res, i, b_fnum);

		/*
		 * The binary representation of INT4 is in network byte order, which
		 * we'd better coerce to the local byte order.
		 */
		ival = ntohl(*((uint32_t *) iptr));

		/*
		 * The binary representation of TEXT is, well, text, and since libpq
		 * was nice enough to append a zero byte to it, it'll work just fine
		 * as a C string.
		 *
		 * The binary representation of BYTEA is a bunch of bytes, which could
		 * include embedded nulls so we have to pay attention to field length.
		 */
		blen = PQgetlength(res, i, b_fnum);

		printf("tuple %d: got\n", i);
		printf(" i = (%d bytes) %d\n",
			   PQgetlength(res, i, i_fnum), ival);
		printf(" t = (%d bytes) '%s'\n",
			   PQgetlength(res, i, t_fnum), tptr);
		printf(" b = (%d bytes) ", blen);
		for (j = 0; j < blen; j++)
			printf("\\%03o", bptr[j]);
		printf("\n\n");
	}
}