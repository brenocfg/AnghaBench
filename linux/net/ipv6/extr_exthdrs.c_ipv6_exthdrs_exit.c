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
 int /*<<< orphan*/  IPPROTO_DSTOPTS ; 
 int /*<<< orphan*/  IPPROTO_NONE ; 
 int /*<<< orphan*/  IPPROTO_ROUTING ; 
 int /*<<< orphan*/  destopt_protocol ; 
 int /*<<< orphan*/  inet6_del_protocol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodata_protocol ; 
 int /*<<< orphan*/  rthdr_protocol ; 

void ipv6_exthdrs_exit(void)
{
	inet6_del_protocol(&nodata_protocol, IPPROTO_NONE);
	inet6_del_protocol(&destopt_protocol, IPPROTO_DSTOPTS);
	inet6_del_protocol(&rthdr_protocol, IPPROTO_ROUTING);
}