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
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (long) ; 
 int mincore (void*,unsigned long,unsigned char*) ; 
 int /*<<< orphan*/  mpx_dig_abort () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

long nr_incore(void *ptr, unsigned long size_bytes)
{
	int i;
	long ret = 0;
	long vec_len = size_bytes / PAGE_SIZE;
	unsigned char *vec = malloc(vec_len);
	int incore_ret;

	if (!vec)
		mpx_dig_abort();

	incore_ret = mincore(ptr, size_bytes, vec);
	if (incore_ret) {
		printf("mincore ret: %d\n", incore_ret);
		perror("mincore");
		mpx_dig_abort();
	}
	for (i = 0; i < vec_len; i++)
		ret += vec[i];
	free(vec);
	return ret;
}