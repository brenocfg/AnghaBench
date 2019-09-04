#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union tpacket_uhdr {TYPE_5__* h1; TYPE_4__* h2; TYPE_3__* h3; void* raw; } ;
struct sockaddr_ll {int dummy; } ;
struct TYPE_7__ {scalar_t__ sk_type; } ;
struct TYPE_6__ {int frame_size; } ;
struct packet_sock {int tp_version; int tp_tx_has_off; int tp_hdrlen; TYPE_2__ sk; TYPE_1__ tx_ring; } ;
struct TYPE_10__ {int tp_len; int tp_net; int tp_mac; } ;
struct TYPE_9__ {int tp_len; int tp_net; int tp_mac; } ;
struct TYPE_8__ {int tp_len; int tp_net; int tp_mac; int /*<<< orphan*/  tp_next_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 scalar_t__ SOCK_DGRAM ; 
#define  TPACKET_V2 129 
#define  TPACKET_V3 128 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tpacket_parse_header(struct packet_sock *po, void *frame,
				int size_max, void **data)
{
	union tpacket_uhdr ph;
	int tp_len, off;

	ph.raw = frame;

	switch (po->tp_version) {
	case TPACKET_V3:
		if (ph.h3->tp_next_offset != 0) {
			pr_warn_once("variable sized slot not supported");
			return -EINVAL;
		}
		tp_len = ph.h3->tp_len;
		break;
	case TPACKET_V2:
		tp_len = ph.h2->tp_len;
		break;
	default:
		tp_len = ph.h1->tp_len;
		break;
	}
	if (unlikely(tp_len > size_max)) {
		pr_err("packet size is too long (%d > %d)\n", tp_len, size_max);
		return -EMSGSIZE;
	}

	if (unlikely(po->tp_tx_has_off)) {
		int off_min, off_max;

		off_min = po->tp_hdrlen - sizeof(struct sockaddr_ll);
		off_max = po->tx_ring.frame_size - tp_len;
		if (po->sk.sk_type == SOCK_DGRAM) {
			switch (po->tp_version) {
			case TPACKET_V3:
				off = ph.h3->tp_net;
				break;
			case TPACKET_V2:
				off = ph.h2->tp_net;
				break;
			default:
				off = ph.h1->tp_net;
				break;
			}
		} else {
			switch (po->tp_version) {
			case TPACKET_V3:
				off = ph.h3->tp_mac;
				break;
			case TPACKET_V2:
				off = ph.h2->tp_mac;
				break;
			default:
				off = ph.h1->tp_mac;
				break;
			}
		}
		if (unlikely((off < off_min) || (off_max < off)))
			return -EINVAL;
	} else {
		off = po->tp_hdrlen - sizeof(struct sockaddr_ll);
	}

	*data = frame + off;
	return tp_len;
}