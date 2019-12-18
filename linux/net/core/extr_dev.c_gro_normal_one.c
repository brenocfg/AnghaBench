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
struct sk_buff {int /*<<< orphan*/  list; } ;
struct napi_struct {scalar_t__ rx_count; int /*<<< orphan*/  rx_list; } ;

/* Variables and functions */
 scalar_t__ gro_normal_batch ; 
 int /*<<< orphan*/  gro_normal_list (struct napi_struct*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gro_normal_one(struct napi_struct *napi, struct sk_buff *skb)
{
	list_add_tail(&skb->list, &napi->rx_list);
	if (++napi->rx_count >= gro_normal_batch)
		gro_normal_list(napi);
}