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
struct sock_extended_err {int ee_origin; int ee_type; int ee_code; scalar_t__ ee_data; scalar_t__ ee_info; } ;
struct scm_timestamping {TYPE_1__* ts; } ;
struct cmsghdr {int cmsg_level; int cmsg_type; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
#define  IPV6_RECVERR 137 
#define  IP_RECVERR 136 
 int /*<<< orphan*/  SOF_TIMESTAMPING_TX_HARDWARE ; 
#define  SOL_IP 135 
#define  SOL_IPV6 134 
#define  SOL_SOCKET 133 
#define  SO_EE_ORIGIN_ICMP 132 
#define  SO_EE_ORIGIN_ICMP6 131 
#define  SO_EE_ORIGIN_LOCAL 130 
#define  SO_EE_ORIGIN_TIMESTAMPING 129 
#define  SO_EE_ORIGIN_ZEROCOPY 128 
 int SO_TIMESTAMPING ; 
 int /*<<< orphan*/  cfg_tx_ts ; 
 int /*<<< orphan*/  cfg_verbose ; 
 int /*<<< orphan*/  error (int,int,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stat_tx_ts ; 
 int /*<<< orphan*/  stat_tx_ts_errors ; 
 int /*<<< orphan*/  stat_zcopies ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void flush_cmsg(struct cmsghdr *cmsg)
{
	struct sock_extended_err *err;
	struct scm_timestamping *tss;
	__u32 lo;
	__u32 hi;
	int i;

	switch (cmsg->cmsg_level) {
	case SOL_SOCKET:
		if (cmsg->cmsg_type == SO_TIMESTAMPING) {
			i = (cfg_tx_ts == SOF_TIMESTAMPING_TX_HARDWARE) ? 2 : 0;
			tss = (struct scm_timestamping *)CMSG_DATA(cmsg);
			if (tss->ts[i].tv_sec == 0)
				stat_tx_ts_errors++;
		} else {
			error(1, 0, "unknown SOL_SOCKET cmsg type=%u\n",
			      cmsg->cmsg_type);
		}
		break;
	case SOL_IP:
	case SOL_IPV6:
		switch (cmsg->cmsg_type) {
		case IP_RECVERR:
		case IPV6_RECVERR:
		{
			err = (struct sock_extended_err *)CMSG_DATA(cmsg);
			switch (err->ee_origin) {
			case SO_EE_ORIGIN_TIMESTAMPING:
				/* Got a TX timestamp from error queue */
				stat_tx_ts++;
				break;
			case SO_EE_ORIGIN_ICMP:
			case SO_EE_ORIGIN_ICMP6:
				if (cfg_verbose)
					fprintf(stderr,
						"received ICMP error: type=%u, code=%u\n",
						err->ee_type, err->ee_code);
				break;
			case SO_EE_ORIGIN_ZEROCOPY:
			{
				lo = err->ee_info;
				hi = err->ee_data;
				/* range of IDs acknowledged */
				stat_zcopies += hi - lo + 1;
				break;
			}
			case SO_EE_ORIGIN_LOCAL:
				if (cfg_verbose)
					fprintf(stderr,
						"received packet with local origin: %u\n",
						err->ee_origin);
				break;
			default:
				error(0, 1, "received packet with origin: %u",
				      err->ee_origin);
			}
			break;
		}
		default:
			error(0, 1, "unknown IP msg type=%u\n",
			      cmsg->cmsg_type);
			break;
		}
		break;
	default:
		error(0, 1, "unknown cmsg level=%u\n",
		      cmsg->cmsg_level);
	}
}