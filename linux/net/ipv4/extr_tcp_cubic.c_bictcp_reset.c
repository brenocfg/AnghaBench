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
struct bictcp {scalar_t__ found; scalar_t__ tcp_cwnd; scalar_t__ ack_cnt; scalar_t__ epoch_start; scalar_t__ delay_min; scalar_t__ bic_K; scalar_t__ bic_origin_point; scalar_t__ last_time; scalar_t__ last_cwnd; scalar_t__ last_max_cwnd; scalar_t__ cnt; } ;

/* Variables and functions */

__attribute__((used)) static inline void bictcp_reset(struct bictcp *ca)
{
	ca->cnt = 0;
	ca->last_max_cwnd = 0;
	ca->last_cwnd = 0;
	ca->last_time = 0;
	ca->bic_origin_point = 0;
	ca->bic_K = 0;
	ca->delay_min = 0;
	ca->epoch_start = 0;
	ca->ack_cnt = 0;
	ca->tcp_cwnd = 0;
	ca->found = 0;
}