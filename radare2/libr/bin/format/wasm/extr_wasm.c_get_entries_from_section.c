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
typedef  scalar_t__ ut32 ;
struct TYPE_6__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {scalar_t__ payload_len; scalar_t__ count; int /*<<< orphan*/  name; int /*<<< orphan*/  payload_data; } ;
typedef  int /*<<< orphan*/  (* RListFree ) (void*) ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  TYPE_1__ RBinWasmSection ;
typedef  TYPE_2__ RBinWasmObj ;
typedef  void* (* ParseEntryFcn ) (int /*<<< orphan*/ *,scalar_t__) ;

/* Variables and functions */
 int /*<<< orphan*/  R_BUF_SET ; 
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_buf_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ *) ; 
 scalar_t__ r_buf_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/  (*) (void*)) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RList *get_entries_from_section (RBinWasmObj *bin, RBinWasmSection *sec, ParseEntryFcn parse_entry, RListFree free_entry) {
	r_return_val_if_fail (sec && bin, NULL);

	RList *ret = r_list_newf (free_entry);
	if (!ret) {
		return NULL;
	}
	RBuffer *b = bin->buf;
	r_buf_seek (b, sec->payload_data, R_BUF_SET);
	ut32 r = 0;
	ut64 max = r_buf_tell (b) + sec->payload_len - 1;
	if (!(max < r_buf_size (b))) {
		goto beach;
	}
	while (r_buf_tell (b) <= max && r < sec->count) {
		void *entry = parse_entry (b, max);
		if (!entry) {
			goto beach;
		}

		if (!r_list_append (ret, entry)) {
			free_entry (entry);
			// should this jump to beach?
		}
		r++;
	}
	return ret;
beach:
	eprintf ("[wasm] error: beach reading entries for section %s\n", sec->name);
	return ret;
}