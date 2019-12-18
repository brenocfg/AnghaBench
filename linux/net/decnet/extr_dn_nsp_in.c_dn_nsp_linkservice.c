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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sk_buff {char* data; int len; } ;
struct dn_scp {unsigned char services_rem; unsigned char flowrem_dat; char flowrem_oth; int /*<<< orphan*/  flowrem_sw; int /*<<< orphan*/  numoth_rcv; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DN_DONTSEND ; 
 int /*<<< orphan*/  DN_SEND ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 unsigned char NSP_FC_MASK ; 
 unsigned char NSP_FC_SCMC ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  dn_nsp_output (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_send_oth_ack (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_add (int /*<<< orphan*/ *,int) ; 
 scalar_t__ seq_next (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void dn_nsp_linkservice(struct sock *sk, struct sk_buff *skb)
{
	struct dn_scp *scp = DN_SK(sk);
	unsigned short segnum;
	unsigned char lsflags;
	signed char fcval;
	int wake_up = 0;
	char *ptr = skb->data;
	unsigned char fctype = scp->services_rem & NSP_FC_MASK;

	if (skb->len != 4)
		goto out;

	segnum = le16_to_cpu(*(__le16 *)ptr);
	ptr += 2;
	lsflags = *(unsigned char *)ptr++;
	fcval = *ptr;

	/*
	 * Here we ignore erronous packets which should really
	 * should cause a connection abort. It is not critical
	 * for now though.
	 */
	if (lsflags & 0xf8)
		goto out;

	if (seq_next(scp->numoth_rcv, segnum)) {
		seq_add(&scp->numoth_rcv, 1);
		switch(lsflags & 0x04) { /* FCVAL INT */
		case 0x00: /* Normal Request */
			switch(lsflags & 0x03) { /* FCVAL MOD */
			case 0x00: /* Request count */
				if (fcval < 0) {
					unsigned char p_fcval = -fcval;
					if ((scp->flowrem_dat > p_fcval) &&
					    (fctype == NSP_FC_SCMC)) {
						scp->flowrem_dat -= p_fcval;
					}
				} else if (fcval > 0) {
					scp->flowrem_dat += fcval;
					wake_up = 1;
				}
				break;
			case 0x01: /* Stop outgoing data */
				scp->flowrem_sw = DN_DONTSEND;
				break;
			case 0x02: /* Ok to start again */
				scp->flowrem_sw = DN_SEND;
				dn_nsp_output(sk);
				wake_up = 1;
			}
			break;
		case 0x04: /* Interrupt Request */
			if (fcval > 0) {
				scp->flowrem_oth += fcval;
				wake_up = 1;
			}
			break;
		}
		if (wake_up && !sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
	}

	dn_nsp_send_oth_ack(sk);

out:
	kfree_skb(skb);
}