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
struct mon_text_ptr {scalar_t__ cnt; scalar_t__ limit; scalar_t__ pbuf; } ;
struct mon_reader_text {int dummy; } ;
struct mon_event_text {char type; int status; int interval; int start_frame; int error_count; } ;

/* Variables and functions */
 scalar_t__ snprintf (scalar_t__,scalar_t__,char*,int,int,int,...) ; 

__attribute__((used)) static void mon_text_read_isostat(struct mon_reader_text *rp,
	struct mon_text_ptr *p, const struct mon_event_text *ep)
{
	if (ep->type == 'S') {
		p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
		    " %d:%d:%d", ep->status, ep->interval, ep->start_frame);
	} else {
		p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
		    " %d:%d:%d:%d",
		    ep->status, ep->interval, ep->start_frame, ep->error_count);
	}
}