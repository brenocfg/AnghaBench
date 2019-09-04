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
 int /*<<< orphan*/  MSG_ZEROCOPY ; 
 int /*<<< orphan*/  cfg_alen ; 
 scalar_t__ cfg_connected ; 
 int /*<<< orphan*/  cfg_dst_addr ; 
 int cfg_mss ; 
 int cfg_payload_len ; 
 scalar_t__ cfg_zerocopy ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_udp(int fd, char *data)
{
	int ret, total_len, len, count = 0;

	total_len = cfg_payload_len;

	while (total_len) {
		len = total_len < cfg_mss ? total_len : cfg_mss;

		ret = sendto(fd, data, len, cfg_zerocopy ? MSG_ZEROCOPY : 0,
			     cfg_connected ? NULL : (void *)&cfg_dst_addr,
			     cfg_connected ? 0 : cfg_alen);
		if (ret == -1)
			error(1, errno, "write");
		if (ret != len)
			error(1, errno, "write: %uB != %uB\n", ret, len);

		total_len -= len;
		count++;
	}

	return count;
}