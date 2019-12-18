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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 size_t nla_total_size (int) ; 
 size_t nla_total_size_64bit (int) ; 

__attribute__((used)) static size_t tcp_opt_stats_get_size(void)
{
	return
		nla_total_size_64bit(sizeof(u64)) + /* TCP_NLA_BUSY */
		nla_total_size_64bit(sizeof(u64)) + /* TCP_NLA_RWND_LIMITED */
		nla_total_size_64bit(sizeof(u64)) + /* TCP_NLA_SNDBUF_LIMITED */
		nla_total_size_64bit(sizeof(u64)) + /* TCP_NLA_DATA_SEGS_OUT */
		nla_total_size_64bit(sizeof(u64)) + /* TCP_NLA_TOTAL_RETRANS */
		nla_total_size_64bit(sizeof(u64)) + /* TCP_NLA_PACING_RATE */
		nla_total_size_64bit(sizeof(u64)) + /* TCP_NLA_DELIVERY_RATE */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_SND_CWND */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_REORDERING */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_MIN_RTT */
		nla_total_size(sizeof(u8)) + /* TCP_NLA_RECUR_RETRANS */
		nla_total_size(sizeof(u8)) + /* TCP_NLA_DELIVERY_RATE_APP_LMT */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_SNDQ_SIZE */
		nla_total_size(sizeof(u8)) + /* TCP_NLA_CA_STATE */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_SND_SSTHRESH */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_DELIVERED */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_DELIVERED_CE */
		nla_total_size_64bit(sizeof(u64)) + /* TCP_NLA_BYTES_SENT */
		nla_total_size_64bit(sizeof(u64)) + /* TCP_NLA_BYTES_RETRANS */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_DSACK_DUPS */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_REORD_SEEN */
		nla_total_size(sizeof(u32)) + /* TCP_NLA_SRTT */
		0;
}