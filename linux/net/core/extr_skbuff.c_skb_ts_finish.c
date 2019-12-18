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
struct ts_state {int dummy; } ;
struct ts_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_SKB_CB (struct ts_state*) ; 
 int /*<<< orphan*/  skb_abort_seq_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skb_ts_finish(struct ts_config *conf, struct ts_state *state)
{
	skb_abort_seq_read(TS_SKB_CB(state));
}