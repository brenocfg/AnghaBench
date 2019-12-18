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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  esp_restore_header (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static void esp_output_restore_header(struct sk_buff *skb)
{
	esp_restore_header(skb, skb_transport_offset(skb) - sizeof(__be32));
}