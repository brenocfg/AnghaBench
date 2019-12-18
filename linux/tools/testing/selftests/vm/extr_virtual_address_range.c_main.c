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
 int MAP_ANONYMOUS ; 
 int /*<<< orphan*/  MAP_CHUNK_SIZE ; 
 char* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int NR_CHUNKS_HIGH ; 
 int NR_CHUNKS_LOW ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 char* hind_addr () ; 
 char* mmap (char*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ validate_addr (char*,int) ; 
 scalar_t__ validate_lower_address_hint () ; 

int main(int argc, char *argv[])
{
	char *ptr[NR_CHUNKS_LOW];
	char *hptr[NR_CHUNKS_HIGH];
	char *hint;
	unsigned long i, lchunks, hchunks;

	for (i = 0; i < NR_CHUNKS_LOW; i++) {
		ptr[i] = mmap(NULL, MAP_CHUNK_SIZE, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (ptr[i] == MAP_FAILED) {
			if (validate_lower_address_hint())
				return 1;
			break;
		}

		if (validate_addr(ptr[i], 0))
			return 1;
	}
	lchunks = i;

	for (i = 0; i < NR_CHUNKS_HIGH; i++) {
		hint = hind_addr();
		hptr[i] = mmap(hint, MAP_CHUNK_SIZE, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (hptr[i] == MAP_FAILED)
			break;

		if (validate_addr(hptr[i], 1))
			return 1;
	}
	hchunks = i;

	for (i = 0; i < lchunks; i++)
		munmap(ptr[i], MAP_CHUNK_SIZE);

	for (i = 0; i < hchunks; i++)
		munmap(hptr[i], MAP_CHUNK_SIZE);

	return 0;
}