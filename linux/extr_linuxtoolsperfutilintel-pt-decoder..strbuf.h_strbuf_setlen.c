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
struct strbuf {size_t alloc; size_t len; char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int strbuf_grow (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int strbuf_setlen(struct strbuf *sb, size_t len) {
	if (!sb->alloc) {
		int ret = strbuf_grow(sb, 0);
		if (ret)
			return ret;
	}
	assert(len < sb->alloc);
	sb->len = len;
	sb->buf[len] = '\0';
	return 0;
}