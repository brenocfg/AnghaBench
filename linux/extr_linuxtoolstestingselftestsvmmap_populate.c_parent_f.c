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
 int /*<<< orphan*/  BUG_ON (int,char*) ; 
 int /*<<< orphan*/  MMAP_SZ ; 
 int /*<<< orphan*/  MS_SYNC ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int msync (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int write (int,int*,int) ; 

__attribute__((used)) static int parent_f(int sock, unsigned long *smap, int child)
{
	int status, ret;

	ret = read(sock, &status, sizeof(int));
	BUG_ON(ret <= 0, "read(sock)");

	*smap = 0x22222BAD;
	ret = msync(smap, MMAP_SZ, MS_SYNC);
	BUG_ON(ret, "msync()");

	ret = write(sock, &status, sizeof(int));
	BUG_ON(ret <= 0, "write(sock)");

	waitpid(child, &status, 0);
	BUG_ON(!WIFEXITED(status), "child in unexpected state");

	return WEXITSTATUS(status);
}