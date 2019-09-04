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
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 scalar_t__ read (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skipn(int fd, off_t n)
{
	char buf[4096];
	ssize_t ret;

	while (n > 0) {
		ret = read(fd, buf, min(n, (off_t)sizeof(buf)));
		if (ret <= 0)
			return ret;
		n -= ret;
	}

	return 0;
}