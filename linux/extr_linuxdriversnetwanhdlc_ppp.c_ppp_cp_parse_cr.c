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
typedef  int /*<<< orphan*/  valid_accm ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_CONF_ACK ; 
 int /*<<< orphan*/  CP_CONF_NAK ; 
 int /*<<< orphan*/  CP_CONF_REJ ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  LCP_OPTION_ACCM 130 
#define  LCP_OPTION_MAGIC 129 
#define  LCP_OPTION_MRU 128 
 scalar_t__ PID_LCP ; 
 int /*<<< orphan*/  RCR_BAD ; 
 int /*<<< orphan*/  RCR_GOOD ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int const*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int const) ; 
 int /*<<< orphan*/  ppp_cp_event (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int const*) ; 

__attribute__((used)) static void ppp_cp_parse_cr(struct net_device *dev, u16 pid, u8 id,
			    unsigned int req_len, const u8 *data)
{
	static u8 const valid_accm[6] = { LCP_OPTION_ACCM, 6, 0, 0, 0, 0 };
	const u8 *opt;
	u8 *out;
	unsigned int len = req_len, nak_len = 0, rej_len = 0;

	if (!(out = kmalloc(len, GFP_ATOMIC))) {
		dev->stats.rx_dropped++;
		return;	/* out of memory, ignore CR packet */
	}

	for (opt = data; len; len -= opt[1], opt += opt[1]) {
		if (len < 2 || len < opt[1]) {
			dev->stats.rx_errors++;
			kfree(out);
			return; /* bad packet, drop silently */
		}

		if (pid == PID_LCP)
			switch (opt[0]) {
			case LCP_OPTION_MRU:
				continue; /* MRU always OK and > 1500 bytes? */

			case LCP_OPTION_ACCM: /* async control character map */
				if (!memcmp(opt, valid_accm,
					    sizeof(valid_accm)))
					continue;
				if (!rej_len) { /* NAK it */
					memcpy(out + nak_len, valid_accm,
					       sizeof(valid_accm));
					nak_len += sizeof(valid_accm);
					continue;
				}
				break;
			case LCP_OPTION_MAGIC:
				if (opt[1] != 6 || (!opt[2] && !opt[3] &&
						    !opt[4] && !opt[5]))
					break; /* reject invalid magic number */
				continue;
			}
		/* reject this option */
		memcpy(out + rej_len, opt, opt[1]);
		rej_len += opt[1];
	}

	if (rej_len)
		ppp_cp_event(dev, pid, RCR_BAD, CP_CONF_REJ, id, rej_len, out);
	else if (nak_len)
		ppp_cp_event(dev, pid, RCR_BAD, CP_CONF_NAK, id, nak_len, out);
	else
		ppp_cp_event(dev, pid, RCR_GOOD, CP_CONF_ACK, id, req_len, data);

	kfree(out);
}