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
 unsigned long BUFLEN ; 
 unsigned long MAX_LEN ; 
 unsigned long MAX_OFFSET ; 
 int /*<<< orphan*/  POISON ; 
 int /*<<< orphan*/  do_one (char*,char*,unsigned long,unsigned long,unsigned long,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* malloc (unsigned long) ; 
 char* memalign (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 

int test_copy_loop(void)
{
	char *src, *dst, *redzone, *fill;
	unsigned long len, src_off, dst_off;
	unsigned long i;

	src = memalign(BUFLEN, BUFLEN);
	dst = memalign(BUFLEN, BUFLEN);
	redzone = malloc(BUFLEN);
	fill = malloc(BUFLEN);

	if (!src || !dst || !redzone || !fill) {
		fprintf(stderr, "malloc failed\n");
		exit(1);
	}

	memset(redzone, POISON, BUFLEN);

	/* Fill with sequential bytes */
	for (i = 0; i < BUFLEN; i++)
		fill[i] = i & 0xff;

	for (len = 1; len < MAX_LEN; len++) {
		for (src_off = 0; src_off < MAX_OFFSET; src_off++) {
			for (dst_off = 0; dst_off < MAX_OFFSET; dst_off++) {
				do_one(src, dst, src_off, dst_off, len,
				       redzone, fill);
			}
		}
	}

	return 0;
}