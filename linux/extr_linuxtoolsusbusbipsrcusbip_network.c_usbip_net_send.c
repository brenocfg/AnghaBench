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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  usbip_net_xmit (int,void*,size_t,int) ; 

ssize_t usbip_net_send(int sockfd, void *buff, size_t bufflen)
{
	return usbip_net_xmit(sockfd, buff, bufflen, 1);
}