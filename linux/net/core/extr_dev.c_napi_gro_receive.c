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
struct napi_struct {int dummy; } ;
typedef  int /*<<< orphan*/  gro_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  napi_skb_finish (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_gro_reset_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mark_napi_id (struct sk_buff*,struct napi_struct*) ; 
 int /*<<< orphan*/  trace_napi_gro_receive_entry (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_napi_gro_receive_exit (int /*<<< orphan*/ ) ; 

gro_result_t napi_gro_receive(struct napi_struct *napi, struct sk_buff *skb)
{
	gro_result_t ret;

	skb_mark_napi_id(skb, napi);
	trace_napi_gro_receive_entry(skb);

	skb_gro_reset_offset(skb);

	ret = napi_skb_finish(dev_gro_receive(napi, skb), skb);
	trace_napi_gro_receive_exit(ret);

	return ret;
}