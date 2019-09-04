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
struct batadv_frag_packet {int dummy; } ;

/* Variables and functions */
 int BATADV_FRAG_MAX_FRAGMENTS ; 
 int BATADV_FRAG_MAX_FRAG_SIZE ; 

__attribute__((used)) static int batadv_frag_size_limit(void)
{
	int limit = BATADV_FRAG_MAX_FRAG_SIZE;

	limit -= sizeof(struct batadv_frag_packet);
	limit *= BATADV_FRAG_MAX_FRAGMENTS;

	return limit;
}