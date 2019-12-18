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
typedef  int /*<<< orphan*/  uint8 ;
struct PktStreamStat {int final_done; } ;
typedef  int /*<<< orphan*/  PushFilter ;

/* Variables and functions */
 int pushf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * render_newlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pkt_stream_flush(PushFilter *next, void *priv)
{
	int			res;
	uint8		hdr[8];
	uint8	   *h = hdr;
	struct PktStreamStat *st = priv;

	/* stream MUST end with normal packet. */
	if (!st->final_done)
	{
		h = render_newlen(h, 0);
		res = pushf_write(next, hdr, h - hdr);
		if (res < 0)
			return res;
		st->final_done = 1;
	}
	return 0;
}