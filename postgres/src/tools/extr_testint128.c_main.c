#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_3__ {int hi; int lo; } ;
struct TYPE_4__ {int i128; TYPE_1__ hl; int /*<<< orphan*/  I128; } ;
typedef  TYPE_2__ test128 ;
typedef  int int64 ;
typedef  int int128 ;

/* Variables and functions */
 void* get_random_uint64 () ; 
 int /*<<< orphan*/  int128_add_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  int128_add_int64_mul_int64 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  int128_add_uint64 (int /*<<< orphan*/ *,scalar_t__) ; 
 int int128_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int my_int128_compare (int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 long strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	long		count;

	if (argc >= 2)
		count = strtol(argv[1], NULL, 0);
	else
		count = 1000000000;

	while (count-- > 0)
	{
		int64		x = get_random_uint64();
		int64		y = get_random_uint64();
		int64		z = get_random_uint64();
		test128		t1;
		test128		t2;

		/* check unsigned addition */
		t1.hl.hi = x;
		t1.hl.lo = y;
		t2 = t1;
		t1.i128 += (int128) (uint64) z;
		int128_add_uint64(&t2.I128, (uint64) z);

		if (t1.hl.hi != t2.hl.hi || t1.hl.lo != t2.hl.lo)
		{
			printf("%016lX%016lX + unsigned %lX\n", x, y, z);
			printf("native = %016lX%016lX\n", t1.hl.hi, t1.hl.lo);
			printf("result = %016lX%016lX\n", t2.hl.hi, t2.hl.lo);
			return 1;
		}

		/* check signed addition */
		t1.hl.hi = x;
		t1.hl.lo = y;
		t2 = t1;
		t1.i128 += (int128) z;
		int128_add_int64(&t2.I128, z);

		if (t1.hl.hi != t2.hl.hi || t1.hl.lo != t2.hl.lo)
		{
			printf("%016lX%016lX + signed %lX\n", x, y, z);
			printf("native = %016lX%016lX\n", t1.hl.hi, t1.hl.lo);
			printf("result = %016lX%016lX\n", t2.hl.hi, t2.hl.lo);
			return 1;
		}

		/* check multiplication */
		t1.i128 = (int128) x * (int128) y;

		t2.hl.hi = t2.hl.lo = 0;
		int128_add_int64_mul_int64(&t2.I128, x, y);

		if (t1.hl.hi != t2.hl.hi || t1.hl.lo != t2.hl.lo)
		{
			printf("%lX * %lX\n", x, y);
			printf("native = %016lX%016lX\n", t1.hl.hi, t1.hl.lo);
			printf("result = %016lX%016lX\n", t2.hl.hi, t2.hl.lo);
			return 1;
		}

		/* check comparison */
		t1.hl.hi = x;
		t1.hl.lo = y;
		t2.hl.hi = z;
		t2.hl.lo = get_random_uint64();

		if (my_int128_compare(t1.i128, t2.i128) !=
			int128_compare(t1.I128, t2.I128))
		{
			printf("comparison failure: %d vs %d\n",
				   my_int128_compare(t1.i128, t2.i128),
				   int128_compare(t1.I128, t2.I128));
			printf("arg1 = %016lX%016lX\n", t1.hl.hi, t1.hl.lo);
			printf("arg2 = %016lX%016lX\n", t2.hl.hi, t2.hl.lo);
			return 1;
		}

		/* check case with identical hi parts; above will hardly ever hit it */
		t2.hl.hi = x;

		if (my_int128_compare(t1.i128, t2.i128) !=
			int128_compare(t1.I128, t2.I128))
		{
			printf("comparison failure: %d vs %d\n",
				   my_int128_compare(t1.i128, t2.i128),
				   int128_compare(t1.I128, t2.I128));
			printf("arg1 = %016lX%016lX\n", t1.hl.hi, t1.hl.lo);
			printf("arg2 = %016lX%016lX\n", t2.hl.hi, t2.hl.lo);
			return 1;
		}
	}

	return 0;
}