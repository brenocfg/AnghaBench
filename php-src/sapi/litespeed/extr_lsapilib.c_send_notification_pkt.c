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
struct lsapi_packet_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ LSAPI_PACKET_HEADER_LEN ; 
 scalar_t__ write (int,struct lsapi_packet_header*,scalar_t__) ; 

__attribute__((used)) static inline int send_notification_pkt( int fd, struct lsapi_packet_header *pkt )
{
    if ( write( fd, pkt, LSAPI_PACKET_HEADER_LEN ) < LSAPI_PACKET_HEADER_LEN )
        return -1;
    return 0;
}