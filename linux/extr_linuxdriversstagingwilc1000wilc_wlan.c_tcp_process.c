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
typedef  int u32 ;
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {int /*<<< orphan*/  txq_spinlock; } ;
struct txq_entry_t {void* buffer; } ;
struct tcphdr {int doff; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  seq; } ;
struct net_device {int dummy; } ;
struct iphdr {scalar_t__ protocol; int ihl; int /*<<< orphan*/  tot_len; } ;
struct ethhdr {scalar_t__ h_proto; } ;
struct TYPE_2__ {int seq_num; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 int MAX_TCP_SESSION ; 
 TYPE_1__* ack_session_info ; 
 int /*<<< orphan*/  add_tcp_pending_ack (int,int,struct txq_entry_t*) ; 
 int /*<<< orphan*/  add_tcp_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tcp_session ; 
 int /*<<< orphan*/  update_tcp_session (int,int) ; 

__attribute__((used)) static inline void tcp_process(struct net_device *dev, struct txq_entry_t *tqe)
{
	void *buffer = tqe->buffer;
	const struct ethhdr *eth_hdr_ptr = buffer;
	int i;
	unsigned long flags;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	if (eth_hdr_ptr->h_proto == htons(ETH_P_IP)) {
		const struct iphdr *ip_hdr_ptr = buffer + ETH_HLEN;

		if (ip_hdr_ptr->protocol == IPPROTO_TCP) {
			const struct tcphdr *tcp_hdr_ptr;
			u32 IHL, total_length, data_offset;

			IHL = ip_hdr_ptr->ihl << 2;
			tcp_hdr_ptr = buffer + ETH_HLEN + IHL;
			total_length = ntohs(ip_hdr_ptr->tot_len);

			data_offset = tcp_hdr_ptr->doff << 2;
			if (total_length == (IHL + data_offset)) {
				u32 seq_no, ack_no;

				seq_no = ntohl(tcp_hdr_ptr->seq);
				ack_no = ntohl(tcp_hdr_ptr->ack_seq);
				for (i = 0; i < tcp_session; i++) {
					u32 j = ack_session_info[i].seq_num;

					if (i < 2 * MAX_TCP_SESSION &&
					    j == seq_no) {
						update_tcp_session(i, ack_no);
						break;
					}
				}
				if (i == tcp_session)
					add_tcp_session(0, 0, seq_no);

				add_tcp_pending_ack(ack_no, i, tqe);
			}
		}
	}
	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);
}