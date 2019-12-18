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
 int AF_INET6 ; 
 int /*<<< orphan*/  set_pktinfo_v4 (int) ; 
 int /*<<< orphan*/  set_recverr_v4 (int) ; 
 int /*<<< orphan*/  set_recverr_v6 (int) ; 
 int /*<<< orphan*/  set_recvpktinfo_v6 (int) ; 

__attribute__((used)) static void set_recv_attr(int sd, int version)
{
	if (version == AF_INET6) {
		set_recvpktinfo_v6(sd);
		set_recverr_v6(sd);
	} else {
		set_pktinfo_v4(sd);
		set_recverr_v4(sd);
	}
}