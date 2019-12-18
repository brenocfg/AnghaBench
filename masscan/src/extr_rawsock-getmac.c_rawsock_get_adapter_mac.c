#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sa_family; int /*<<< orphan*/  sa_data; } ;
struct TYPE_4__ {TYPE_1__ ifru_hwaddr; } ;
struct ifreq {TYPE_2__ ifr_ifru; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG (int,char*,char const*,...) ; 
 int /*<<< orphan*/  SIOCGIFHWADDR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int
rawsock_get_adapter_mac(const char *ifname, unsigned char *mac)
{
    int fd;
    int x;
    struct ifreq ifr;


    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("socket");
        goto end;
    }

    strcpy_s(ifr.ifr_name, IFNAMSIZ, ifname);
    x = ioctl(fd, SIOCGIFHWADDR, (char *)&ifr);
    if (x < 0) {
        perror("ioctl");
        goto end;
    }

    /* Log helpful info about the interface type */
    switch (ifr.ifr_ifru.ifru_hwaddr.sa_family) {
    case 1:
        LOG(1, "if:%s: type=ethernet(1)\n", ifname);
        break;
    default:
        LOG(1, "if:%s: type=0x%04x\n", ifname, ifr.ifr_ifru.ifru_hwaddr.sa_family);
    }


    memcpy(mac, ifr.ifr_ifru.ifru_hwaddr.sa_data, 6);

    /*
     * [KLUDGE]
     *  For VPN tunnels with raw IP there isn't a hardware address, so just
     *  return a fake one instead.
     */
    if (memcmp(mac, "\0\0\0\0\0\0", 6) == 0
            && ifr.ifr_ifru.ifru_hwaddr.sa_family == 0xfffe) {
        LOG(1, "%s: creating fake address\n", ifname);
        mac[5] = 1;
    }

end:
    close(fd);
    return 0;
}