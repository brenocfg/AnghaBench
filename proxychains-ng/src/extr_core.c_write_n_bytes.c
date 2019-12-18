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
 int write (int,char*,size_t) ; 

__attribute__((used)) static int write_n_bytes(int fd, char *buff, size_t size) {
	int i = 0;
	size_t wrote = 0;
	for(;;) {
		i = write(fd, &buff[wrote], size - wrote);
		if(i <= 0)
			return i;
		wrote += i;
		if(wrote == size)
			return wrote;
	}
}