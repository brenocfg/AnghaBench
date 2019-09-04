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
struct strbuf {scalar_t__ len; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 int strbuf_grow (struct strbuf*,size_t) ; 
 int strbuf_setlen (struct strbuf*,scalar_t__) ; 

int strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
	int ret = strbuf_grow(sb, len);
	if (ret)
		return ret;

	memcpy(sb->buf + sb->len, data, len);
	return strbuf_setlen(sb, sb->len + len);
}