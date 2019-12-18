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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  errno ; 
 int write (int,unsigned char*,size_t) ; 

__attribute__((used)) static int trywrite(int fd, void* buf, size_t bytes) {
	ssize_t ret;
	unsigned char *out = buf;
again:
	ret = write(fd, out, bytes);
	switch(ret) {
		case -1:
			if(errno == EINTR) goto again;
		case  0:
			return 0;
		default:
			if(ret == bytes || !bytes) return 1;
			out += ret;
			bytes -= ret;
			goto again;
	}
}