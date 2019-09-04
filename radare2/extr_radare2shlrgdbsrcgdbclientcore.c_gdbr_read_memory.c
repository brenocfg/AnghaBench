#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
struct TYPE_4__ {int page_size; } ;
typedef  TYPE_1__ libgdbr_t ;

/* Variables and functions */
 int gdbr_read_memory_page (TYPE_1__*,int,int /*<<< orphan*/ *,int) ; 

int gdbr_read_memory(libgdbr_t *g, ut64 address, ut8 *buf, int len) {
	int ret_len, ret, tmp;
	int page_size = g->page_size;
	ret_len = 0;
	// Read and round up to page size
	tmp = page_size - (address & (page_size - 1));
	if (tmp >= len) {
		return gdbr_read_memory_page (g, address, buf, len);
	}
	if ((ret = gdbr_read_memory_page (g, address, buf, tmp)) != tmp) {
		return ret;
	}
	len -= tmp;
	address += tmp;
	buf += tmp;
	ret_len += ret;
	// Read complete pages
	while (len > page_size) {
		if ((ret = gdbr_read_memory_page (g, address, buf, page_size)) != page_size) {
			if (ret < 1) {
				return ret_len;
			}
			return ret_len + ret;
		}
		len -= page_size;
		address += page_size;
		buf += page_size;
		ret_len += page_size;
	}
	// Read left-overs
	if ((ret = gdbr_read_memory_page (g, address, buf, len)) < 0) {
		return ret_len;
	}
	return ret_len + ret;
}