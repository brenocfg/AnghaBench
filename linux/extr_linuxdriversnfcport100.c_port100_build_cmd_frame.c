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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct port100 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT100_FRAME_HEADER_LEN ; 
 int /*<<< orphan*/  PORT100_FRAME_TAIL_LEN ; 
 int /*<<< orphan*/  port100_tx_frame_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port100_tx_frame_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port100_tx_update_payload_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port100_build_cmd_frame(struct port100 *dev, u8 cmd_code,
				    struct sk_buff *skb)
{
	/* payload is already there, just update datalen */
	int payload_len = skb->len;

	skb_push(skb, PORT100_FRAME_HEADER_LEN);
	skb_put(skb, PORT100_FRAME_TAIL_LEN);

	port100_tx_frame_init(skb->data, cmd_code);
	port100_tx_update_payload_len(skb->data, payload_len);
	port100_tx_frame_finish(skb->data);
}