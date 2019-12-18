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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 int SOF_TIMESTAMPING_OPT_CMSG ; 
 int SOF_TIMESTAMPING_OPT_ID ; 
 int SOF_TIMESTAMPING_OPT_TSONLY ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_SOFTWARE ; 
 scalar_t__ SOF_TIMESTAMPING_TX_SOFTWARE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TIMESTAMPING ; 
 scalar_t__ cfg_tx_ts ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void set_tx_timestamping(int fd)
{
	int val = SOF_TIMESTAMPING_OPT_CMSG | SOF_TIMESTAMPING_OPT_ID |
			SOF_TIMESTAMPING_OPT_TSONLY;

	if (cfg_tx_ts == SOF_TIMESTAMPING_TX_SOFTWARE)
		val |= SOF_TIMESTAMPING_SOFTWARE;
	else
		val |= SOF_TIMESTAMPING_RAW_HARDWARE;

	if (setsockopt(fd, SOL_SOCKET, SO_TIMESTAMPING, &val, sizeof(val)))
		error(1, errno, "setsockopt tx timestamping");
}