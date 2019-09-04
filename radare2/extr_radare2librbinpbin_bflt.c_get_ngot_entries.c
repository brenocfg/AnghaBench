#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;
struct r_bin_bflt_obj {int size; int /*<<< orphan*/  b; TYPE_1__* hdr; } ;
struct TYPE_2__ {int data_end; int data_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALID_GOT_ENTRY (int) ; 
 int r_buf_read_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int get_ngot_entries(struct r_bin_bflt_obj *obj) {
	ut32 data_size = obj->hdr->data_end - obj->hdr->data_start;
	int i = 0, n_got = 0;
	if (data_size > obj->size) {
		return 0;
	}
	for (i = 0, n_got = 0; i < data_size; i += 4, n_got++) {
		ut32 entry, offset = obj->hdr->data_start;
		if (offset + i + sizeof (ut32) > obj->size ||
		    offset + i + sizeof (ut32) < offset) {
			return 0;
		}
		int len = r_buf_read_at (obj->b, offset + i, (ut8 *) &entry,
			sizeof (ut32));
		if (len != sizeof (ut32)) {
			return 0;
		}
		if (!VALID_GOT_ENTRY (entry)) {
			break;
		}
	}
	return n_got;
}