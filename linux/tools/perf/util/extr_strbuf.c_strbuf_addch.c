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
struct strbuf {int* buf; size_t len; } ;

/* Variables and functions */
 int strbuf_grow (struct strbuf*,int) ; 

int strbuf_addch(struct strbuf *sb, int c)
{
	int ret = strbuf_grow(sb, 1);
	if (ret)
		return ret;

	sb->buf[sb->len++] = c;
	sb->buf[sb->len] = '\0';
	return 0;
}