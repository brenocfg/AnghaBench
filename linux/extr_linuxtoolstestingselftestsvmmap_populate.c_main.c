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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int,char*) ; 
 unsigned long* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MMAP_SZ ; 
 int /*<<< orphan*/  MS_SYNC ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int child_f (int,unsigned long*,int /*<<< orphan*/ ) ; 
 int close (int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fork () ; 
 int ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long* mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msync (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parent_f (int,unsigned long*,int) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * tmpfile () ; 

int main(int argc, char **argv)
{
	int sock[2], child, ret;
	FILE *ftmp;
	unsigned long *smap;

	ftmp = tmpfile();
	BUG_ON(ftmp == 0, "tmpfile()");

	ret = ftruncate(fileno(ftmp), MMAP_SZ);
	BUG_ON(ret, "ftruncate()");

	smap = mmap(0, MMAP_SZ, PROT_READ | PROT_WRITE,
			MAP_SHARED, fileno(ftmp), 0);
	BUG_ON(smap == MAP_FAILED, "mmap()");

	*smap = 0xdeadbabe;
	/* Probably unnecessary, but let it be. */
	ret = msync(smap, MMAP_SZ, MS_SYNC);
	BUG_ON(ret, "msync()");

	ret = socketpair(PF_LOCAL, SOCK_SEQPACKET, 0, sock);
	BUG_ON(ret, "socketpair()");

	child = fork();
	BUG_ON(child == -1, "fork()");

	if (child) {
		ret = close(sock[0]);
		BUG_ON(ret, "close()");

		return parent_f(sock[1], smap, child);
	}

	ret = close(sock[1]);
	BUG_ON(ret, "close()");

	return child_f(sock[0], smap, fileno(ftmp));
}