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
typedef  int u32 ;
struct rsvp_head {int tgenerator; int* tmap; } ;

/* Variables and functions */

__attribute__((used)) static int tunnel_bts(struct rsvp_head *data)
{
	int n = data->tgenerator >> 5;
	u32 b = 1 << (data->tgenerator & 0x1F);

	if (data->tmap[n] & b)
		return 0;
	data->tmap[n] |= b;
	return 1;
}