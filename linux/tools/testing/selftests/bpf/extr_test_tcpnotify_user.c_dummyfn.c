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
struct tcp_notifier {int type; int subtype; int source; int hash; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  rx_callbacks ; 

__attribute__((used)) static void dummyfn(void *ctx, int cpu, void *data, __u32 size)
{
	struct tcp_notifier *t = data;

	if (t->type != 0xde || t->subtype != 0xad ||
	    t->source != 0xbe || t->hash != 0xef)
		return;
	rx_callbacks++;
}