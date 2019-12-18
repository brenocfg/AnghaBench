#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msghdr {int msg_iovlen; TYPE_1__* msg_iov; } ;
struct TYPE_2__ {unsigned char* iov_base; int iov_len; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int msg_verify_data(struct msghdr *msg, int size, int chunk_sz)
{
	int i, j, bytes_cnt = 0;
	unsigned char k = 0;

	for (i = 0; i < msg->msg_iovlen; i++) {
		unsigned char *d = msg->msg_iov[i].iov_base;

		for (j = 0;
		     j < msg->msg_iov[i].iov_len && size; j++) {
			if (d[j] != k++) {
				fprintf(stderr,
					"detected data corruption @iov[%i]:%i %02x != %02x, %02x ?= %02x\n",
					i, j, d[j], k - 1, d[j+1], k);
				return -EIO;
			}
			bytes_cnt++;
			if (bytes_cnt == chunk_sz) {
				k = 0;
				bytes_cnt = 0;
			}
			size--;
		}
	}
	return 0;
}