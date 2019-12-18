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

/* Variables and functions */
 int ITERATIONS ; 
 int LARGE_ITERATIONS ; 
 unsigned long LARGE_MAX_OFFSET ; 
 unsigned long LARGE_SIZE ; 
 int /*<<< orphan*/  LARGE_SIZE_START ; 
 unsigned long MAX_OFFSET_DIFF_S1_S2 ; 
 unsigned long SIZE ; 
 int /*<<< orphan*/  exit (int) ; 
 char* memalign (int,unsigned long) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int random () ; 
 int /*<<< orphan*/  srandom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_one (char*,char*,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int testcase(bool islarge)
{
	char *s1;
	char *s2;
	unsigned long i;

	unsigned long comp_size = (islarge ? LARGE_SIZE : SIZE);
	unsigned long alloc_size = comp_size + MAX_OFFSET_DIFF_S1_S2;
	int iterations = islarge ? LARGE_ITERATIONS : ITERATIONS;

	s1 = memalign(128, alloc_size);
	if (!s1) {
		perror("memalign");
		exit(1);
	}

	s2 = memalign(128, alloc_size);
	if (!s2) {
		perror("memalign");
		exit(1);
	}

	srandom(time(0));

	for (i = 0; i < iterations; i++) {
		unsigned long j;
		unsigned long change;
		char *rand_s1 = s1;
		char *rand_s2 = s2;

		for (j = 0; j < alloc_size; j++)
			s1[j] = random();

		rand_s1 += random() % MAX_OFFSET_DIFF_S1_S2;
		rand_s2 += random() % MAX_OFFSET_DIFF_S1_S2;
		memcpy(rand_s2, rand_s1, comp_size);

		/* change one byte */
		change = random() % comp_size;
		rand_s2[change] = random() & 0xff;

		if (islarge)
			test_one(rand_s1, rand_s2, LARGE_MAX_OFFSET,
					LARGE_SIZE_START, comp_size);
		else
			test_one(rand_s1, rand_s2, SIZE, 0, comp_size);
	}

	srandom(time(0));

	for (i = 0; i < iterations; i++) {
		unsigned long j;
		unsigned long change;
		char *rand_s1 = s1;
		char *rand_s2 = s2;

		for (j = 0; j < alloc_size; j++)
			s1[j] = random();

		rand_s1 += random() % MAX_OFFSET_DIFF_S1_S2;
		rand_s2 += random() % MAX_OFFSET_DIFF_S1_S2;
		memcpy(rand_s2, rand_s1, comp_size);

		/* change multiple bytes, 1/8 of total */
		for (j = 0; j < comp_size / 8; j++) {
			change = random() % comp_size;
			s2[change] = random() & 0xff;
		}

		if (islarge)
			test_one(rand_s1, rand_s2, LARGE_MAX_OFFSET,
					LARGE_SIZE_START, comp_size);
		else
			test_one(rand_s1, rand_s2, SIZE, 0, comp_size);
	}

	return 0;
}