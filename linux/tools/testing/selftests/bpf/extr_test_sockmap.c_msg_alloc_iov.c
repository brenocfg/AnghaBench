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
struct msghdr {int msg_iovlen; struct iovec* msg_iov; } ;
struct iovec {unsigned char* iov_base; int iov_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int msg_alloc_iov(struct msghdr *msg,
			 int iov_count, int iov_length,
			 bool data, bool xmit)
{
	unsigned char k = 0;
	struct iovec *iov;
	int i;

	iov = calloc(iov_count, sizeof(struct iovec));
	if (!iov)
		return errno;

	for (i = 0; i < iov_count; i++) {
		unsigned char *d = calloc(iov_length, sizeof(char));

		if (!d) {
			fprintf(stderr, "iov_count %i/%i OOM\n", i, iov_count);
			goto unwind_iov;
		}
		iov[i].iov_base = d;
		iov[i].iov_len = iov_length;

		if (data && xmit) {
			int j;

			for (j = 0; j < iov_length; j++)
				d[j] = k++;
		}
	}

	msg->msg_iov = iov;
	msg->msg_iovlen = iov_count;

	return 0;
unwind_iov:
	for (i--; i >= 0 ; i--)
		free(msg->msg_iov[i].iov_base);
	return -ENOMEM;
}