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
struct napi_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void net_dm_packet_trace_napi_poll_hit(void *ignore,
					      struct napi_struct *napi,
					      int work, int budget)
{
}