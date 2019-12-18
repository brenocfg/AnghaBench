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
typedef  int /*<<< orphan*/  decimal ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  CDECIMALTYPE ; 
 int /*<<< orphan*/  ECPGdebug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGTYPESdecimal_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PGTYPESdecimal_new () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  check_errno () ; 
 int decadd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int deccmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int deccvasc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int deccvint (int,int /*<<< orphan*/ *) ; 
 int deccvlong (long,int /*<<< orphan*/ *) ; 
 int decdiv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decmul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__* decs ; 
 int decsub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dectoasc (int /*<<< orphan*/ *,char*,int,int) ; 
 int dectodbl (int /*<<< orphan*/ *,double*) ; 
 int dectoint (int /*<<< orphan*/ *,int*) ; 
 int dectolong (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  print_double (double) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int) ; 
 scalar_t__ risnull (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsetnull (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

int
main(void)
{
	decimal *dec, *din;
	char buf[BUFSIZE];
	long l;
	int i, j, k, q, r, count = 0;
	double dbl;
	decimal **decarr = (decimal **) calloc(1, sizeof(decimal));

	ECPGdebug(1, stderr);

	for (i = 0; decs[i]; i++)
	{
		dec = PGTYPESdecimal_new();
		r = deccvasc(decs[i], strlen(decs[i]), dec);
		if (r)
		{
			check_errno();
			printf("dec[%d,0]: r: %d\n", i, r);
			PGTYPESdecimal_free(dec);
			continue;
		}
		decarr = realloc(decarr, sizeof(decimal *) * (count + 1));
		decarr[count++] = dec;

		r = dectoasc(dec, buf, BUFSIZE-1, -1);
		if (r < 0) check_errno();
		printf("dec[%d,1]: r: %d, %s\n", i, r, buf);

		r = dectoasc(dec, buf, BUFSIZE-1, 0);
		if (r < 0) check_errno();
		printf("dec[%d,2]: r: %d, %s\n", i, r, buf);
		r = dectoasc(dec, buf, BUFSIZE-1, 1);
		if (r < 0) check_errno();
		printf("dec[%d,3]: r: %d, %s\n", i, r, buf);
		r = dectoasc(dec, buf, BUFSIZE-1, 2);
		if (r < 0) check_errno();
		printf("dec[%d,4]: r: %d, %s\n", i, r, buf);

		din = PGTYPESdecimal_new();
		r = dectoasc(din, buf, BUFSIZE-1, 2);
		if (r < 0) check_errno();
		printf("dec[%d,5]: r: %d, %s\n", i, r, buf);

		r = dectolong(dec, &l);
		if (r) check_errno();
		printf("dec[%d,6]: %ld (r: %d)\n", i, r?0L:l, r);
		if (r == 0)
		{
			r = deccvlong(l, din);
			if (r) check_errno();
			dectoasc(din, buf, BUFSIZE-1, 2);
			q = deccmp(dec, din);
			printf("dec[%d,7]: %s (r: %d - cmp: %d)\n", i, buf, r, q);
		}

		r = dectoint(dec, &k);
		if (r) check_errno();
		printf("dec[%d,8]: %d (r: %d)\n", i, r?0:k, r);
		if (r == 0)
		{
			r = deccvint(k, din);
			if (r) check_errno();
			dectoasc(din, buf, BUFSIZE-1, 2);
			q = deccmp(dec, din);
			printf("dec[%d,9]: %s (r: %d - cmp: %d)\n", i, buf, r, q);
		}

		if (i != 6)
		{
			/* underflow does not work reliable on several archs, so not testing it here */
			/* this is a libc problem since we only call strtod() */
			r = dectodbl(dec, &dbl);
			if (r) check_errno();
			printf("dec[%d,10]: ", i);
			print_double(r ? 0.0 : dbl);
			printf(" (r: %d)\n", r);
		}

		PGTYPESdecimal_free(din);
		printf("\n");
	}

	/* add a NULL value */
	dec = PGTYPESdecimal_new();
	decarr = realloc(decarr, sizeof(decimal *) * (count + 1));
	decarr[count++] = dec;

	rsetnull(CDECIMALTYPE, (char *) decarr[count-1]);
	printf("dec[%d]: %sNULL\n", count-1,
		risnull(CDECIMALTYPE, (char *) decarr[count-1]) ? "" : "NOT ");
	printf("dec[0]: %sNULL\n",
		risnull(CDECIMALTYPE, (char *) decarr[0]) ? "" : "NOT ");

	r = dectoasc(decarr[3], buf, -1, -1);
	check_errno(); printf("dectoasc with len == -1: r: %d\n", r);
	r = dectoasc(decarr[3], buf, 0, -1);
	check_errno(); printf("dectoasc with len == 0: r: %d\n", r);

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < count; j++)
		{
			decimal a, s, m, d;
			int c;
			c = deccmp(decarr[i], decarr[j]);
			printf("dec[c,%d,%d]: %d\n", i, j, c);

			r = decadd(decarr[i], decarr[j], &a);
			if (r)
			{
				check_errno();
				printf("r: %d\n", r);
			}
			else
			{
				dectoasc(&a, buf, BUFSIZE-1, -1);
				printf("dec[a,%d,%d]: %s\n", i, j, buf);
			}

			r = decsub(decarr[i], decarr[j], &s);
			if (r)
			{
				check_errno();
				printf("r: %d\n", r);
			}
			else
			{
				dectoasc(&s, buf, BUFSIZE-1, -1);
				printf("dec[s,%d,%d]: %s\n", i, j, buf);
			}

			r = decmul(decarr[i], decarr[j], &m);
			if (r)
			{
				check_errno();
				printf("r: %d\n", r);
			}
			else
			{
				dectoasc(&m, buf, BUFSIZE-1, -1);
				printf("dec[m,%d,%d]: %s\n", i, j, buf);
			}

			r = decdiv(decarr[i], decarr[j], &d);
			if (r)
			{
				check_errno();
				printf("r: %d\n", r);
			}
			else
			{
				dectoasc(&d, buf, BUFSIZE-1, -1);
				printf("dec[d,%d,%d]: %s\n", i, j, buf);
			}
		}
	}

	for (i = 0; i < count; i++)
	{
		dectoasc(decarr[i], buf, BUFSIZE-1, -1);
		printf("%d: %s\n", i, buf);

		PGTYPESdecimal_free(decarr[i]);
	}
	free(decarr);

	return 0;
}