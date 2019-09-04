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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct jffs2_sb_info {size_t wbuf_len; size_t wbuf_pagesize; scalar_t__ wbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static size_t jffs2_fill_wbuf(struct jffs2_sb_info *c, const uint8_t *buf,
			      size_t len)
{
	if (len && !c->wbuf_len && (len >= c->wbuf_pagesize))
		return 0;

	if (len > (c->wbuf_pagesize - c->wbuf_len))
		len = c->wbuf_pagesize - c->wbuf_len;
	memcpy(c->wbuf + c->wbuf_len, buf, len);
	c->wbuf_len += (uint32_t) len;
	return len;
}