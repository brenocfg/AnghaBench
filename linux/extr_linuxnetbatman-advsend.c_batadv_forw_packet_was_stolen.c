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
struct batadv_forw_packet {int /*<<< orphan*/  cleanup_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
batadv_forw_packet_was_stolen(struct batadv_forw_packet *forw_packet)
{
	return !hlist_unhashed(&forw_packet->cleanup_list);
}