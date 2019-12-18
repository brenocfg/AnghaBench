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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 scalar_t__ CHECK_FAIL (int) ; 
 scalar_t__ accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_started ; 
 int /*<<< orphan*/  server_started_mtx ; 

__attribute__((used)) static void *server_thread(void *arg)
{
	struct sockaddr_storage addr;
	socklen_t len = sizeof(addr);
	int fd = *(int *)arg;
	int client_fd;
	int err;

	err = listen(fd, 1);

	pthread_mutex_lock(&server_started_mtx);
	pthread_cond_signal(&server_started);
	pthread_mutex_unlock(&server_started_mtx);

	if (CHECK_FAIL(err < 0)) {
		perror("Failed to listed on socket");
		return NULL;
	}

	client_fd = accept(fd, (struct sockaddr *)&addr, &len);
	if (CHECK_FAIL(client_fd < 0)) {
		perror("Failed to accept client");
		return NULL;
	}

	/* Wait for the next connection (that never arrives)
	 * to keep this thread alive to prevent calling
	 * close() on client_fd.
	 */
	if (CHECK_FAIL(accept(fd, (struct sockaddr *)&addr, &len) >= 0)) {
		perror("Unexpected success in second accept");
		return NULL;
	}

	close(client_fd);

	return NULL;
}