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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t gtp_get_size(const struct net_device *dev)
{
	return nla_total_size(sizeof(__u32));	/* IFLA_GTP_PDP_HASHSIZE */
}