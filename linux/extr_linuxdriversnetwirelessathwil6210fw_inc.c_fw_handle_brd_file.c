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
struct wil_fw_record_brd_file {int /*<<< orphan*/  max_size_bytes; int /*<<< orphan*/  base_addr; } ;
struct wil6210_priv {void* brd_file_max_size; void* brd_file_addr; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_fw (struct wil6210_priv*,char*,void*,void*) ; 
 int /*<<< orphan*/  wil_err_fw (struct wil6210_priv*,char*,size_t) ; 

__attribute__((used)) static int
fw_handle_brd_file(struct wil6210_priv *wil, const void *data,
		   size_t size)
{
	const struct wil_fw_record_brd_file *rec = data;

	if (size < sizeof(*rec)) {
		wil_err_fw(wil, "brd_file record too short: %zu\n", size);
		return 0;
	}

	wil->brd_file_addr = le32_to_cpu(rec->base_addr);
	wil->brd_file_max_size = le32_to_cpu(rec->max_size_bytes);

	wil_dbg_fw(wil, "brd_file_addr 0x%x, brd_file_max_size %d\n",
		   wil->brd_file_addr, wil->brd_file_max_size);

	return 0;
}