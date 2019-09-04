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
struct packet_sock {scalar_t__ xmit; } ;

/* Variables and functions */
 scalar_t__ packet_direct_xmit ; 

__attribute__((used)) static bool packet_use_direct_xmit(const struct packet_sock *po)
{
	return po->xmit == packet_direct_xmit;
}