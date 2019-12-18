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
typedef  scalar_t__ u16 ;
struct l2cap_chan {void* sport; void* psm; int /*<<< orphan*/  src_type; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
typedef  void* __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 scalar_t__ L2CAP_PSM_AUTO_END ; 
 scalar_t__ L2CAP_PSM_DYN_START ; 
 scalar_t__ L2CAP_PSM_LE_DYN_END ; 
 scalar_t__ L2CAP_PSM_LE_DYN_START ; 
 scalar_t__ __l2cap_global_chan_by_addr (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_list_lock ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int l2cap_add_psm(struct l2cap_chan *chan, bdaddr_t *src, __le16 psm)
{
	int err;

	write_lock(&chan_list_lock);

	if (psm && __l2cap_global_chan_by_addr(psm, src, chan->src_type)) {
		err = -EADDRINUSE;
		goto done;
	}

	if (psm) {
		chan->psm = psm;
		chan->sport = psm;
		err = 0;
	} else {
		u16 p, start, end, incr;

		if (chan->src_type == BDADDR_BREDR) {
			start = L2CAP_PSM_DYN_START;
			end = L2CAP_PSM_AUTO_END;
			incr = 2;
		} else {
			start = L2CAP_PSM_LE_DYN_START;
			end = L2CAP_PSM_LE_DYN_END;
			incr = 1;
		}

		err = -EINVAL;
		for (p = start; p <= end; p += incr)
			if (!__l2cap_global_chan_by_addr(cpu_to_le16(p), src,
							 chan->src_type)) {
				chan->psm   = cpu_to_le16(p);
				chan->sport = cpu_to_le16(p);
				err = 0;
				break;
			}
	}

done:
	write_unlock(&chan_list_lock);
	return err;
}