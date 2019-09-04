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
typedef  void* u16 ;
struct rio_channel {scalar_t__ state; int /*<<< orphan*/  comp; void* rem_channel; } ;
struct rio_ch_chan_hdr {int /*<<< orphan*/  src_ch; int /*<<< orphan*/  dst_ch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ RIO_CM_CONNECT ; 
 int /*<<< orphan*/  RIO_CM_CONNECTED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_exch (struct rio_channel*,int /*<<< orphan*/ ) ; 
 struct rio_channel* riocm_get_channel (void*) ; 
 int /*<<< orphan*/  riocm_put_channel (struct rio_channel*) ; 

__attribute__((used)) static int riocm_resp_handler(void *resp_data)
{
	struct rio_channel *ch;
	struct rio_ch_chan_hdr *hh = resp_data;
	u16 chnum;

	chnum = ntohs(hh->dst_ch);
	ch = riocm_get_channel(chnum);
	if (!ch)
		return -ENODEV;

	if (ch->state != RIO_CM_CONNECT) {
		riocm_put_channel(ch);
		return -EINVAL;
	}

	riocm_exch(ch, RIO_CM_CONNECTED);
	ch->rem_channel = ntohs(hh->src_ch);
	complete(&ch->comp);
	riocm_put_channel(ch);

	return 0;
}