#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_6__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {scalar_t__ payload_data; scalar_t__ payload_len; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  TYPE_1__ RBinWasmSection ;
typedef  TYPE_2__ RBinWasmObj ;
typedef  int /*<<< orphan*/  RBinWasmCustomNameEntry ;

/* Variables and functions */
 int /*<<< orphan*/  R_BUF_SET ; 
 int /*<<< orphan*/ * parse_custom_name_entry (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  r_buf_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ *) ; 
 scalar_t__ r_buf_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_new () ; 

__attribute__((used)) static RList *r_bin_wasm_get_custom_name_entries (RBinWasmObj *bin, RBinWasmSection *sec) {
	RList *ret = r_list_new ();

	RBuffer *buf = bin->buf;

	r_buf_seek (buf, sec->payload_data, R_BUF_SET);
	ut64 max = sec->payload_data + sec->payload_len - 1;

	if (max > r_buf_size (buf)) {
		goto beach;
	}

	while (r_buf_tell (buf) < max) {
		RBinWasmCustomNameEntry *nam = parse_custom_name_entry (buf, max);

		if (!nam) {
			goto beach;
		}

		if (!r_list_append (ret, nam)) {
			goto beach;
		}
	}

	return ret;
beach:
	r_list_free (ret);
	return NULL;
}