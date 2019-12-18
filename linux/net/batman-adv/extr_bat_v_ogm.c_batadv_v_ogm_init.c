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
struct TYPE_2__ {unsigned char* ogm_buff; int /*<<< orphan*/  ogm_buff_mutex; int /*<<< orphan*/  ogm_wq; int /*<<< orphan*/  ogm_seqno; int /*<<< orphan*/  ogm_buff_len; } ;
struct batadv_priv {TYPE_1__ bat_v; } ;
struct batadv_ogm2_packet {int /*<<< orphan*/  throughput; int /*<<< orphan*/  flags; int /*<<< orphan*/  ttl; int /*<<< orphan*/  version; int /*<<< orphan*/  packet_type; } ;
typedef  int /*<<< orphan*/  random_seqno ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_COMPAT_VERSION ; 
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int /*<<< orphan*/  BATADV_OGM2 ; 
 int /*<<< orphan*/  BATADV_OGM2_HLEN ; 
 int /*<<< orphan*/  BATADV_THROUGHPUT_MAX_VALUE ; 
 int /*<<< orphan*/  BATADV_TTL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_v_ogm_send ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 unsigned char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int batadv_v_ogm_init(struct batadv_priv *bat_priv)
{
	struct batadv_ogm2_packet *ogm_packet;
	unsigned char *ogm_buff;
	u32 random_seqno;

	bat_priv->bat_v.ogm_buff_len = BATADV_OGM2_HLEN;
	ogm_buff = kzalloc(bat_priv->bat_v.ogm_buff_len, GFP_ATOMIC);
	if (!ogm_buff)
		return -ENOMEM;

	bat_priv->bat_v.ogm_buff = ogm_buff;
	ogm_packet = (struct batadv_ogm2_packet *)ogm_buff;
	ogm_packet->packet_type = BATADV_OGM2;
	ogm_packet->version = BATADV_COMPAT_VERSION;
	ogm_packet->ttl = BATADV_TTL;
	ogm_packet->flags = BATADV_NO_FLAGS;
	ogm_packet->throughput = htonl(BATADV_THROUGHPUT_MAX_VALUE);

	/* randomize initial seqno to avoid collision */
	get_random_bytes(&random_seqno, sizeof(random_seqno));
	atomic_set(&bat_priv->bat_v.ogm_seqno, random_seqno);
	INIT_DELAYED_WORK(&bat_priv->bat_v.ogm_wq, batadv_v_ogm_send);

	mutex_init(&bat_priv->bat_v.ogm_buff_mutex);

	return 0;
}