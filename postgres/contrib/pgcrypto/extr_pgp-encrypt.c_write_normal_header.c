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
typedef  int /*<<< orphan*/  PushFilter ;

/* Variables and functions */
 int pushf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * render_newlen (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
write_normal_header(PushFilter *dst, int tag, int len)
{
	uint8		hdr[8];
	uint8	   *h = hdr;

	*h++ = 0xC0 | tag;
	h = render_newlen(h, len);
	return pushf_write(dst, hdr, h - hdr);
}