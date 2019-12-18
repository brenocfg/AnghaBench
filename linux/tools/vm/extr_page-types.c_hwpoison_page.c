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
 int /*<<< orphan*/  hwpoison_inject_fd ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sprintf (char*,char*,unsigned long) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int hwpoison_page(unsigned long offset)
{
	char buf[100];
	int len;

	len = sprintf(buf, "0x%lx\n", offset);
	len = write(hwpoison_inject_fd, buf, len);
	if (len < 0) {
		perror("hwpoison inject");
		return len;
	}
	return 0;
}