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
struct pollfd {int fd; int events; int revents; } ;

/* Variables and functions */
 int POLLIN ; 
 int poll_retry (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  tcp_read_time_out ; 

__attribute__((used)) static int read_n_bytes(int fd, char *buff, size_t size) {
	int ready;
	size_t i;
	struct pollfd pfd[1];

	pfd[0].fd = fd;
	pfd[0].events = POLLIN;
	for(i = 0; i < size; i++) {
		pfd[0].revents = 0;
		ready = poll_retry(pfd, 1, tcp_read_time_out);
		if(ready != 1 || !(pfd[0].revents & POLLIN) || 1 != read(fd, &buff[i], 1))
			return -1;
	}
	return (int) size;
}