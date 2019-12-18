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
struct xsk_socket {int /*<<< orphan*/  ifname; } ;
struct ifreq {char* ifr_name; void* ifr_data; } ;
struct ethtool_channels {int max_combined; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETHTOOL_GCHANNELS ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCETHTOOL ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xsk_get_max_queues(struct xsk_socket *xsk)
{
	struct ethtool_channels channels = { .cmd = ETHTOOL_GCHANNELS };
	struct ifreq ifr = {};
	int fd, err, ret;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
		return -errno;

	ifr.ifr_data = (void *)&channels;
	memcpy(ifr.ifr_name, xsk->ifname, IFNAMSIZ - 1);
	ifr.ifr_name[IFNAMSIZ - 1] = '\0';
	err = ioctl(fd, SIOCETHTOOL, &ifr);
	if (err && errno != EOPNOTSUPP) {
		ret = -errno;
		goto out;
	}

	if (err || channels.max_combined == 0)
		/* If the device says it has no channels, then all traffic
		 * is sent to a single stream, so max queues = 1.
		 */
		ret = 1;
	else
		ret = channels.max_combined;

out:
	close(fd);
	return ret;
}