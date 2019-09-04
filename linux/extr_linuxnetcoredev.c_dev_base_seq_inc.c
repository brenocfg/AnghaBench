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
struct net {scalar_t__ dev_base_seq; } ;

/* Variables and functions */

__attribute__((used)) static inline void dev_base_seq_inc(struct net *net)
{
	while (++net->dev_base_seq == 0)
		;
}