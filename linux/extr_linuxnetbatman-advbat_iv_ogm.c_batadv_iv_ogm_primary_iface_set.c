#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct batadv_ogm_packet {int /*<<< orphan*/  ttl; } ;
struct TYPE_2__ {unsigned char* ogm_buff; } ;
struct batadv_hard_iface {TYPE_1__ bat_iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_TTL ; 

__attribute__((used)) static void
batadv_iv_ogm_primary_iface_set(struct batadv_hard_iface *hard_iface)
{
	struct batadv_ogm_packet *batadv_ogm_packet;
	unsigned char *ogm_buff = hard_iface->bat_iv.ogm_buff;

	batadv_ogm_packet = (struct batadv_ogm_packet *)ogm_buff;
	batadv_ogm_packet->ttl = BATADV_TTL;
}