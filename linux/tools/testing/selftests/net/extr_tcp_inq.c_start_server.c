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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int BUF_SIZE ; 
 scalar_t__ EINTR ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ ) ; 
 int send (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 

void *start_server(void *arg)
{
	int server_fd = (int)(unsigned long)arg;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	char *buf;
	int fd;
	int r;

	buf = malloc(BUF_SIZE);

	for (;;) {
		fd = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
		if (fd == -1) {
			perror("accept");
			break;
		}
		do {
			r = send(fd, buf, BUF_SIZE, 0);
		} while (r < 0 && errno == EINTR);
		if (r < 0)
			perror("send");
		if (r != BUF_SIZE)
			fprintf(stderr, "can only send %d bytes\n", r);
		/* TCP_INQ can overestimate in-queue by one byte if we send
		 * the FIN packet. Sleep for 1 second, so that the client
		 * likely invoked recvmsg().
		 */
		sleep(1);
		close(fd);
	}

	free(buf);
	close(server_fd);
	pthread_exit(0);
}