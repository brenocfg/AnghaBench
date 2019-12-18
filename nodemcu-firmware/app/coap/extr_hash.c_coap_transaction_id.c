#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  ip ;
typedef  int coap_tid_t ;
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ coap_packet_t ;
typedef  int* coap_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  coap_hash (unsigned char const*,int,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void coap_transaction_id(const uint32_t ip, const uint32_t port, const coap_packet_t *pkt, coap_tid_t *id) {
  coap_key_t h;
  memset(h, 0, sizeof(coap_key_t));

  /* Compare the transport address. */
  coap_hash((const unsigned char *)&(port), sizeof(port), h);
  coap_hash((const unsigned char *)&(ip), sizeof(ip), h);
  coap_hash((const unsigned char *)(pkt->hdr.id), sizeof(pkt->hdr.id), h);
  *id = ((h[0] << 8) | h[1]) ^ ((h[2] << 8) | h[3]);
}