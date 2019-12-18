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
typedef  int /*<<< orphan*/  u32 ;
struct batadv_ogm_packet {int ttl; int /*<<< orphan*/  tq; scalar_t__ reserved; int /*<<< orphan*/  flags; int /*<<< orphan*/  version; int /*<<< orphan*/  packet_type; } ;
struct TYPE_2__ {unsigned char* ogm_buff; int /*<<< orphan*/  ogm_buff_mutex; int /*<<< orphan*/  ogm_buff_len; int /*<<< orphan*/  ogm_seqno; } ;
struct batadv_hard_iface {TYPE_1__ bat_iv; } ;
typedef  int /*<<< orphan*/  random_seqno ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_COMPAT_VERSION ; 
 int /*<<< orphan*/  BATADV_IV_OGM ; 
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int /*<<< orphan*/  BATADV_OGM_HLEN ; 
 int /*<<< orphan*/  BATADV_TQ_MAX_VALUE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int batadv_iv_ogm_iface_enable(struct batadv_hard_iface *hard_iface)
{
	struct batadv_ogm_packet *batadv_ogm_packet;
	unsigned char *ogm_buff;
	u32 random_seqno;

	mutex_lock(&hard_iface->bat_iv.ogm_buff_mutex);

	/* randomize initial seqno to avoid collision */
	get_random_bytes(&random_seqno, sizeof(random_seqno));
	atomic_set(&hard_iface->bat_iv.ogm_seqno, random_seqno);

	hard_iface->bat_iv.ogm_buff_len = BATADV_OGM_HLEN;
	ogm_buff = kmalloc(hard_iface->bat_iv.ogm_buff_len, GFP_ATOMIC);
	if (!ogm_buff) {
		mutex_unlock(&hard_iface->bat_iv.ogm_buff_mutex);
		return -ENOMEM;
	}

	hard_iface->bat_iv.ogm_buff = ogm_buff;

	batadv_ogm_packet = (struct batadv_ogm_packet *)ogm_buff;
	batadv_ogm_packet->packet_type = BATADV_IV_OGM;
	batadv_ogm_packet->version = BATADV_COMPAT_VERSION;
	batadv_ogm_packet->ttl = 2;
	batadv_ogm_packet->flags = BATADV_NO_FLAGS;
	batadv_ogm_packet->reserved = 0;
	batadv_ogm_packet->tq = BATADV_TQ_MAX_VALUE;

	mutex_unlock(&hard_iface->bat_iv.ogm_buff_mutex);

	return 0;
}