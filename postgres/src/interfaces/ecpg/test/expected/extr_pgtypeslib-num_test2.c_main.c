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
typedef  int /*<<< orphan*/  numeric ;
typedef  int /*<<< orphan*/  decimal ;

/* Variables and functions */
 int /*<<< orphan*/  ECPGdebug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGTYPESchar_free (char*) ; 
 int /*<<< orphan*/  PGTYPESdecimal_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PGTYPESdecimal_new () ; 
 int PGTYPESnumeric_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PGTYPESnumeric_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PGTYPESnumeric_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PGTYPESnumeric_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PGTYPESnumeric_from_asc (scalar_t__,char**) ; 
 int PGTYPESnumeric_from_decimal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PGTYPESnumeric_from_int (int,int /*<<< orphan*/ *) ; 
 int PGTYPESnumeric_from_long (long,int /*<<< orphan*/ *) ; 
 int PGTYPESnumeric_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PGTYPESnumeric_new () ; 
 int PGTYPESnumeric_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* PGTYPESnumeric_to_asc (int /*<<< orphan*/ *,int) ; 
 int PGTYPESnumeric_to_decimal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PGTYPESnumeric_to_double (int /*<<< orphan*/ *,double*) ; 
 int PGTYPESnumeric_to_int (int /*<<< orphan*/ *,int*) ; 
 int PGTYPESnumeric_to_long (int /*<<< orphan*/ *,long*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  check_errno () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 scalar_t__* nums ; 
 int /*<<< orphan*/  print_double (double) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  stderr ; 

int
main(void)
{
	char *text="error\n";
	char *endptr;
	numeric *num, *nin;
	decimal *dec;
	long l;
	int i, j, k, q, r, count = 0;
	double d;
	numeric **numarr = (numeric **) calloc(1, sizeof(numeric));

	ECPGdebug(1, stderr);

	for (i = 0; nums[i]; i++)
	{
		num = PGTYPESnumeric_from_asc(nums[i], &endptr);
		if (!num) check_errno();
		if (endptr != NULL)
		{
			printf("endptr of %d is not NULL\n", i);
			if (*endptr != '\0')
				printf("*endptr of %d is not \\0\n", i);
		}
		if (!num) continue;

		numarr = realloc(numarr, sizeof(numeric *) * (count + 1));
		numarr[count++] = num;

		text = PGTYPESnumeric_to_asc(num, -1);
		if (!text) check_errno();
		printf("num[%d,1]: %s\n", i, text); PGTYPESchar_free(text);
		text = PGTYPESnumeric_to_asc(num, 0);
		if (!text) check_errno();
		printf("num[%d,2]: %s\n", i, text); PGTYPESchar_free(text);
		text = PGTYPESnumeric_to_asc(num, 1);
		if (!text) check_errno();
		printf("num[%d,3]: %s\n", i, text); PGTYPESchar_free(text);
		text = PGTYPESnumeric_to_asc(num, 2);
		if (!text) check_errno();
		printf("num[%d,4]: %s\n", i, text); PGTYPESchar_free(text);

		nin = PGTYPESnumeric_new();
		text = PGTYPESnumeric_to_asc(nin, 2);
		if (!text) check_errno();
		printf("num[%d,5]: %s\n", i, text); PGTYPESchar_free(text);

		r = PGTYPESnumeric_to_long(num, &l);
		if (r) check_errno();
		printf("num[%d,6]: %ld (r: %d)\n", i, r?0L:l, r);
		if (r == 0)
		{
			r = PGTYPESnumeric_from_long(l, nin);
			if (r) check_errno();
			text = PGTYPESnumeric_to_asc(nin, 2);
			q = PGTYPESnumeric_cmp(num, nin);
			printf("num[%d,7]: %s (r: %d - cmp: %d)\n", i, text, r, q);
			PGTYPESchar_free(text);
		}

		r = PGTYPESnumeric_to_int(num, &k);
		if (r) check_errno();
		printf("num[%d,8]: %d (r: %d)\n", i, r?0:k, r);
		if (r == 0)
		{
			r = PGTYPESnumeric_from_int(k, nin);
			if (r) check_errno();
			text = PGTYPESnumeric_to_asc(nin, 2);
			q = PGTYPESnumeric_cmp(num, nin);
			printf("num[%d,9]: %s (r: %d - cmp: %d)\n", i, text, r, q);
			PGTYPESchar_free(text);
		}

		if (i != 6)
		{
			/* underflow does not work reliable on several archs, so not testing it here */
			/* this is a libc problem since we only call strtod() */

			r = PGTYPESnumeric_to_double(num, &d);
			if (r) check_errno();
			printf("num[%d,10]: ", i);
			print_double(r ? 0.0 : d);
			printf(" (r: %d)\n", r);
		}

		/* do not test double to numeric because
		 * - extra digits are different on different architectures
		 * - PGTYPESnumeric_from_double internally calls PGTYPESnumeric_from_asc anyway
		 */

		dec = PGTYPESdecimal_new();
		r = PGTYPESnumeric_to_decimal(num, dec);
		if (r) check_errno();
		/* we have no special routine for outputting decimal, it would
		 * convert to a numeric anyway */
		printf("num[%d,11]: - (r: %d)\n", i, r);
		if (r == 0)
		{
			r = PGTYPESnumeric_from_decimal(dec, nin);
			if (r) check_errno();
			text = PGTYPESnumeric_to_asc(nin, 2);
			q = PGTYPESnumeric_cmp(num, nin);
			printf("num[%d,12]: %s (r: %d - cmp: %d)\n", i, text, r, q);
			PGTYPESchar_free(text);
		}

		PGTYPESdecimal_free(dec);
		PGTYPESnumeric_free(nin);
		printf("\n");
	}

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < count; j++)
		{
			numeric* a = PGTYPESnumeric_new();
			numeric* s = PGTYPESnumeric_new();
			numeric* m = PGTYPESnumeric_new();
			numeric* d = PGTYPESnumeric_new();
			r = PGTYPESnumeric_add(numarr[i], numarr[j], a);
			if (r)
			{
				check_errno();
				printf("r: %d\n", r);
			}
			else
			{
				text = PGTYPESnumeric_to_asc(a, 10);
				printf("num[a,%d,%d]: %s\n", i, j, text);
				PGTYPESchar_free(text);
			}
			r = PGTYPESnumeric_sub(numarr[i], numarr[j], s);
			if (r)
			{
				check_errno();
				printf("r: %d\n", r);
			}
			else
			{
				text = PGTYPESnumeric_to_asc(s, 10);
				printf("num[s,%d,%d]: %s\n", i, j, text);
				PGTYPESchar_free(text);
			}
			r = PGTYPESnumeric_mul(numarr[i], numarr[j], m);
			if (r)
			{
				check_errno();
				printf("r: %d\n", r);
			}
			else
			{
				text = PGTYPESnumeric_to_asc(m, 10);
				printf("num[m,%d,%d]: %s\n", i, j, text);
				PGTYPESchar_free(text);
			}
			r = PGTYPESnumeric_div(numarr[i], numarr[j], d);
			if (r)
			{
				check_errno();
				printf("r: %d\n", r);
			}
			else
			{
				text = PGTYPESnumeric_to_asc(d, 10);
				printf("num[d,%d,%d]: %s\n", i, j, text);
				PGTYPESchar_free(text);
			}

			PGTYPESnumeric_free(a);
			PGTYPESnumeric_free(s);
			PGTYPESnumeric_free(m);
			PGTYPESnumeric_free(d);
		}
	}

	for (i = 0; i < count; i++)
	{
		text = PGTYPESnumeric_to_asc(numarr[i], -1);
		printf("%d: %s\n", i, text);
		PGTYPESchar_free(text);
		PGTYPESnumeric_free(numarr[i]);
	}
	free(numarr);

	return 0;
}