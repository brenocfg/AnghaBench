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
struct ifreq {int ifr_ifindex; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifdata ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCGIFINDEX ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int get_ifidx(const char *ifname)
{
	struct ifreq ifdata;
	int sd, rc;

	if (!ifname || *ifname == '\0')
		return -1;

	memset(&ifdata, 0, sizeof(ifdata));

	strcpy(ifdata.ifr_name, ifname);

	sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sd < 0) {
		log_err_errno("socket failed");
		return -1;
	}

	rc = ioctl(sd, SIOCGIFINDEX, (char *)&ifdata);
	close(sd);
	if (rc != 0) {
		log_err_errno("ioctl(SIOCGIFINDEX) failed");
		return -1;
	}

	return ifdata.ifr_ifindex;
}