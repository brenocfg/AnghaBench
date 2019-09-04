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
 int BUFSIZ ; 
 int /*<<< orphan*/  do_read (char*,int) ; 

__attribute__((used)) static void skip(int size)
{
	char buf[BUFSIZ];
	int r;

	while (size) {
		r = size > BUFSIZ ? BUFSIZ : size;
		do_read(buf, r);
		size -= r;
	};
}