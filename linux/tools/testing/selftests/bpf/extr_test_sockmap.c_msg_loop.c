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
struct timeval {int tv_sec; int tv_usec; } ;
struct sockmap_options {int drop_expected; int data_test; scalar_t__ sendpage; scalar_t__ verbose; } ;
struct msghdr {int /*<<< orphan*/  member_0; } ;
struct msg_stats {int bytes_sent; float bytes_recvd; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EIO ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int MSG_NOSIGNAL ; 
 int MSG_PEEK ; 
 int O_NONBLOCK ; 
 int clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  fcntl (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,float,float,float) ; 
 int msg_alloc_iov (struct msghdr*,int,int,int,int) ; 
 int /*<<< orphan*/  msg_free_iov (struct msghdr*) ; 
 int msg_verify_data (struct msghdr*,int,int) ; 
 scalar_t__ peek_flag ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int recvmsg (int,struct msghdr*,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int sendmsg (int,struct msghdr*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int txmsg_apply ; 
 scalar_t__ txmsg_cork ; 
 float txmsg_pop ; 

__attribute__((used)) static int msg_loop(int fd, int iov_count, int iov_length, int cnt,
		    struct msg_stats *s, bool tx,
		    struct sockmap_options *opt)
{
	struct msghdr msg = {0}, msg_peek = {0};
	int err, i, flags = MSG_NOSIGNAL;
	bool drop = opt->drop_expected;
	bool data = opt->data_test;

	err = msg_alloc_iov(&msg, iov_count, iov_length, data, tx);
	if (err)
		goto out_errno;
	if (peek_flag) {
		err = msg_alloc_iov(&msg_peek, iov_count, iov_length, data, tx);
		if (err)
			goto out_errno;
	}

	if (tx) {
		clock_gettime(CLOCK_MONOTONIC, &s->start);
		for (i = 0; i < cnt; i++) {
			int sent = sendmsg(fd, &msg, flags);

			if (!drop && sent < 0) {
				perror("send loop error:");
				goto out_errno;
			} else if (drop && sent >= 0) {
				printf("send loop error expected: %i\n", sent);
				errno = -EIO;
				goto out_errno;
			}
			if (sent > 0)
				s->bytes_sent += sent;
		}
		clock_gettime(CLOCK_MONOTONIC, &s->end);
	} else {
		int slct, recvp = 0, recv, max_fd = fd;
		float total_bytes, txmsg_pop_total;
		int fd_flags = O_NONBLOCK;
		struct timeval timeout;
		fd_set w;

		fcntl(fd, fd_flags);
		/* Account for pop bytes noting each iteration of apply will
		 * call msg_pop_data helper so we need to account for this
		 * by calculating the number of apply iterations. Note user
		 * of the tool can create cases where no data is sent by
		 * manipulating pop/push/pull/etc. For example txmsg_apply 1
		 * with txmsg_pop 1 will try to apply 1B at a time but each
		 * iteration will then pop 1B so no data will ever be sent.
		 * This is really only useful for testing edge cases in code
		 * paths.
		 */
		total_bytes = (float)iov_count * (float)iov_length * (float)cnt;
		txmsg_pop_total = txmsg_pop;
		if (txmsg_apply)
			txmsg_pop_total *= (total_bytes / txmsg_apply);
		total_bytes -= txmsg_pop_total;
		err = clock_gettime(CLOCK_MONOTONIC, &s->start);
		if (err < 0)
			perror("recv start time: ");
		while (s->bytes_recvd < total_bytes) {
			if (txmsg_cork) {
				timeout.tv_sec = 0;
				timeout.tv_usec = 300000;
			} else {
				timeout.tv_sec = 3;
				timeout.tv_usec = 0;
			}

			/* FD sets */
			FD_ZERO(&w);
			FD_SET(fd, &w);

			slct = select(max_fd + 1, &w, NULL, NULL, &timeout);
			if (slct == -1) {
				perror("select()");
				clock_gettime(CLOCK_MONOTONIC, &s->end);
				goto out_errno;
			} else if (!slct) {
				if (opt->verbose)
					fprintf(stderr, "unexpected timeout: recved %zu/%f pop_total %f\n", s->bytes_recvd, total_bytes, txmsg_pop_total);
				errno = -EIO;
				clock_gettime(CLOCK_MONOTONIC, &s->end);
				goto out_errno;
			}

			errno = 0;
			if (peek_flag) {
				flags |= MSG_PEEK;
				recvp = recvmsg(fd, &msg_peek, flags);
				if (recvp < 0) {
					if (errno != EWOULDBLOCK) {
						clock_gettime(CLOCK_MONOTONIC, &s->end);
						goto out_errno;
					}
				}
				flags = 0;
			}

			recv = recvmsg(fd, &msg, flags);
			if (recv < 0) {
				if (errno != EWOULDBLOCK) {
					clock_gettime(CLOCK_MONOTONIC, &s->end);
					perror("recv failed()\n");
					goto out_errno;
				}
			}

			s->bytes_recvd += recv;

			if (data) {
				int chunk_sz = opt->sendpage ?
						iov_length * cnt :
						iov_length * iov_count;

				errno = msg_verify_data(&msg, recv, chunk_sz);
				if (errno) {
					perror("data verify msg failed\n");
					goto out_errno;
				}
				if (recvp) {
					errno = msg_verify_data(&msg_peek,
								recvp,
								chunk_sz);
					if (errno) {
						perror("data verify msg_peek failed\n");
						goto out_errno;
					}
				}
			}
		}
		clock_gettime(CLOCK_MONOTONIC, &s->end);
	}

	msg_free_iov(&msg);
	msg_free_iov(&msg_peek);
	return err;
out_errno:
	msg_free_iov(&msg);
	msg_free_iov(&msg_peek);
	return errno;
}