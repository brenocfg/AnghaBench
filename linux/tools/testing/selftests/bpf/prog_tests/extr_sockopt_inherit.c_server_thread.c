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
 int /*<<< orphan*/  CUSTOM_INHERIT1 ; 
 int /*<<< orphan*/  CUSTOM_INHERIT2 ; 
 int /*<<< orphan*/  CUSTOM_LISTENER ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_started ; 
 int /*<<< orphan*/  server_started_mtx ; 
 scalar_t__ verify_sockopt (int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void *server_thread(void *arg)
{
	struct sockaddr_storage addr;
	socklen_t len = sizeof(addr);
	int fd = *(int *)arg;
	int client_fd;
	int err = 0;

	err = listen(fd, 1);

	pthread_mutex_lock(&server_started_mtx);
	pthread_cond_signal(&server_started);
	pthread_mutex_unlock(&server_started_mtx);

	if (CHECK_FAIL(err < 0)) {
		perror("Failed to listed on socket");
		return NULL;
	}

	err += verify_sockopt(fd, CUSTOM_INHERIT1, "listen", 1);
	err += verify_sockopt(fd, CUSTOM_INHERIT2, "listen", 1);
	err += verify_sockopt(fd, CUSTOM_LISTENER, "listen", 1);

	client_fd = accept(fd, (struct sockaddr *)&addr, &len);
	if (CHECK_FAIL(client_fd < 0)) {
		perror("Failed to accept client");
		return NULL;
	}

	err += verify_sockopt(client_fd, CUSTOM_INHERIT1, "accept", 1);
	err += verify_sockopt(client_fd, CUSTOM_INHERIT2, "accept", 1);
	err += verify_sockopt(client_fd, CUSTOM_LISTENER, "accept", 0);

	close(client_fd);

	return (void *)(long)err;
}