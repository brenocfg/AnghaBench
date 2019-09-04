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
struct rio_channel {int /*<<< orphan*/  id; } ;
struct rio_ch_chan_hdr {int /*<<< orphan*/  dst_ch; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RIO_CM_DISCONNECT ; 
 int /*<<< orphan*/  RX_CMD ; 
 int /*<<< orphan*/  ch_idr ; 
 struct rio_channel* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int riocm_ch_close (struct rio_channel*) ; 
 int /*<<< orphan*/  riocm_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  riocm_exch (struct rio_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int riocm_close_handler(void *data)
{
	struct rio_channel *ch;
	struct rio_ch_chan_hdr *hh = data;
	int ret;

	riocm_debug(RX_CMD, "for ch=%d", ntohs(hh->dst_ch));

	spin_lock_bh(&idr_lock);
	ch = idr_find(&ch_idr, ntohs(hh->dst_ch));
	if (!ch) {
		spin_unlock_bh(&idr_lock);
		return -ENODEV;
	}
	idr_remove(&ch_idr, ch->id);
	spin_unlock_bh(&idr_lock);

	riocm_exch(ch, RIO_CM_DISCONNECT);

	ret = riocm_ch_close(ch);
	if (ret)
		riocm_debug(RX_CMD, "riocm_ch_close() returned %d", ret);

	return 0;
}