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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct interface_info {int /*<<< orphan*/  wfdesc; } ;
struct in_addr {int dummy; } ;
struct hardware {int dummy; } ;
struct dhcp_packet {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t INT_MAX ; 
 int WSAEMSGSIZE ; 
 int WSAENETUNREACH ; 
 int /*<<< orphan*/  note (char*,...) ; 
 int sendto (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

ssize_t send_packet( struct interface_info *ip,
                     struct dhcp_packet *p,
                     size_t size,
                     struct in_addr addr,
                     struct sockaddr_in *broadcast,
                     struct hardware *hardware ) {
    int result;

    if (size > INT_MAX)
        return WSAEMSGSIZE;

    result =
        sendto( ip->wfdesc, (char *)p, (int)size, 0,
                (struct sockaddr *)broadcast, sizeof(*broadcast) );

    if (result < 0) {
        note ("send_packet: %x", result);
        if (result == WSAENETUNREACH)
            note ("send_packet: please consult README file%s",
                  " regarding broadcast address.");
    }

    return result;
}