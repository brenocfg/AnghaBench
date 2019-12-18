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
struct sk_buff {int len; void* data; } ;
struct sctp_chunkhdr {scalar_t__ type; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  _ch ;

/* Variables and functions */
 scalar_t__ SCTP_CID_ABORT ; 
 scalar_t__ SCTP_CID_INIT ; 
 scalar_t__ SCTP_CID_SHUTDOWN_COMPLETE ; 
 int SCTP_PAD4 (int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct sctp_chunkhdr* skb_header_pointer (struct sk_buff*,int,int,struct sctp_chunkhdr*) ; 

__attribute__((used)) static int sctp_rcv_ootb(struct sk_buff *skb)
{
	struct sctp_chunkhdr *ch, _ch;
	int ch_end, offset = 0;

	/* Scan through all the chunks in the packet.  */
	do {
		/* Make sure we have at least the header there */
		if (offset + sizeof(_ch) > skb->len)
			break;

		ch = skb_header_pointer(skb, offset, sizeof(*ch), &_ch);

		/* Break out if chunk length is less then minimal. */
		if (ntohs(ch->length) < sizeof(_ch))
			break;

		ch_end = offset + SCTP_PAD4(ntohs(ch->length));
		if (ch_end > skb->len)
			break;

		/* RFC 8.4, 2) If the OOTB packet contains an ABORT chunk, the
		 * receiver MUST silently discard the OOTB packet and take no
		 * further action.
		 */
		if (SCTP_CID_ABORT == ch->type)
			goto discard;

		/* RFC 8.4, 6) If the packet contains a SHUTDOWN COMPLETE
		 * chunk, the receiver should silently discard the packet
		 * and take no further action.
		 */
		if (SCTP_CID_SHUTDOWN_COMPLETE == ch->type)
			goto discard;

		/* RFC 4460, 2.11.2
		 * This will discard packets with INIT chunk bundled as
		 * subsequent chunks in the packet.  When INIT is first,
		 * the normal INIT processing will discard the chunk.
		 */
		if (SCTP_CID_INIT == ch->type && (void *)ch != skb->data)
			goto discard;

		offset = ch_end;
	} while (ch_end < skb->len);

	return 0;

discard:
	return 1;
}