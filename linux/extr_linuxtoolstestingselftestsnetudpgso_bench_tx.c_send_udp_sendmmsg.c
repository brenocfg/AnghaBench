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
struct TYPE_2__ {int msg_iovlen; struct iovec* msg_iov; } ;
struct mmsghdr {TYPE_1__ msg_hdr; } ;
struct iovec {char* iov_base; unsigned int iov_len; } ;
typedef  int /*<<< orphan*/  mmsgs ;

/* Variables and functions */
 int ETH_DATA_LEN ; 
 int ETH_MAX_MTU ; 
 int /*<<< orphan*/  MSG_ZEROCOPY ; 
 unsigned int cfg_mss ; 
 unsigned int cfg_payload_len ; 
 scalar_t__ cfg_zerocopy ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct mmsghdr*,int /*<<< orphan*/ ,int) ; 
 int sendmmsg (int,struct mmsghdr*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_udp_sendmmsg(int fd, char *data)
{
	const int max_nr_msg = ETH_MAX_MTU / ETH_DATA_LEN;
	struct mmsghdr mmsgs[max_nr_msg];
	struct iovec iov[max_nr_msg];
	unsigned int off = 0, left;
	int i = 0, ret;

	memset(mmsgs, 0, sizeof(mmsgs));

	left = cfg_payload_len;
	while (left) {
		if (i == max_nr_msg)
			error(1, 0, "sendmmsg: exceeds max_nr_msg");

		iov[i].iov_base = data + off;
		iov[i].iov_len = cfg_mss < left ? cfg_mss : left;

		mmsgs[i].msg_hdr.msg_iov = iov + i;
		mmsgs[i].msg_hdr.msg_iovlen = 1;

		off += iov[i].iov_len;
		left -= iov[i].iov_len;
		i++;
	}

	ret = sendmmsg(fd, mmsgs, i, cfg_zerocopy ? MSG_ZEROCOPY : 0);
	if (ret == -1)
		error(1, errno, "sendmmsg");

	return ret;
}