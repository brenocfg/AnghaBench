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
struct interface_info {int /*<<< orphan*/  rfdesc; } ;
struct hardware {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t INT_MAX ; 
 int WSAEMSGSIZE ; 
 int recvfrom (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

ssize_t receive_packet(struct interface_info *ip,
                       unsigned char *packet_data,
                       size_t packet_len,
                       struct sockaddr_in *dest,
                       struct hardware *hardware ) {
    int recv_addr_size = sizeof(*dest);
    int result;

    if (packet_len > INT_MAX)
        return WSAEMSGSIZE;

    result =
        recvfrom (ip -> rfdesc, (char *)packet_data, (int)packet_len, 0,
                  (struct sockaddr *)dest, &recv_addr_size );
    return result;
}