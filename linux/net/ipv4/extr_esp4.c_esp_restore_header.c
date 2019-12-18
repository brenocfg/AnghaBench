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
struct sk_buff {scalar_t__ data; } ;
struct ip_esp_hdr {int /*<<< orphan*/  spi; int /*<<< orphan*/  seq_no; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {void* tmp; } ;

/* Variables and functions */
 TYPE_1__* ESP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/ * esp_tmp_extra (void*) ; 

__attribute__((used)) static void esp_restore_header(struct sk_buff *skb, unsigned int offset)
{
	struct ip_esp_hdr *esph = (void *)(skb->data + offset);
	void *tmp = ESP_SKB_CB(skb)->tmp;
	__be32 *seqhi = esp_tmp_extra(tmp);

	esph->seq_no = esph->spi;
	esph->spi = *seqhi;
}