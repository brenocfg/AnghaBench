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
struct buffer_ext {size_t max_sz; size_t cur_pos; void* data; } ;

/* Variables and functions */
 size_t BUFFER_EXT_DFL_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static inline int
buffer_ext_add(struct buffer_ext *be, void *addr, size_t sz)
{
	void *tmp;
	size_t be_sz = be->max_sz;

retry:
	if ((be->cur_pos + sz) < be_sz) {
		memcpy(be->data + be->cur_pos, addr, sz);
		be->cur_pos += sz;
		return 0;
	}

	if (!be_sz)
		be_sz = BUFFER_EXT_DFL_SIZE;
	else
		be_sz <<= 1;

	tmp = realloc(be->data, be_sz);
	if (!tmp)
		return -1;

	be->data   = tmp;
	be->max_sz = be_sz;

	goto retry;
}