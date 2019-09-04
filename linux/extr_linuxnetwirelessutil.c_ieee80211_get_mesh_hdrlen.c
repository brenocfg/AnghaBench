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
struct ieee80211s_hdr {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int __ieee80211_get_mesh_hdrlen (int /*<<< orphan*/ ) ; 

unsigned int ieee80211_get_mesh_hdrlen(struct ieee80211s_hdr *meshhdr)
{
	return __ieee80211_get_mesh_hdrlen(meshhdr->flags);
}