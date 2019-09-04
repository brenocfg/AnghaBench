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
typedef  int /*<<< orphan*/  u32 ;
struct wil6210_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_coredumpv (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 scalar_t__ wil_fw_copy_crash_dump (struct wil6210_priv*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ wil_fw_get_crash_dump_bounds (struct wil6210_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_to_dev (struct wil6210_priv*) ; 

void wil_fw_core_dump(struct wil6210_priv *wil)
{
	void *fw_dump_data;
	u32 fw_dump_size;

	if (wil_fw_get_crash_dump_bounds(wil, &fw_dump_size, NULL)) {
		wil_err(wil, "fail to get fw dump size\n");
		return;
	}

	fw_dump_data = vzalloc(fw_dump_size);
	if (!fw_dump_data)
		return;

	if (wil_fw_copy_crash_dump(wil, fw_dump_data, fw_dump_size)) {
		vfree(fw_dump_data);
		return;
	}
	/* fw_dump_data will be free in device coredump release function
	 * after 5 min
	 */
	dev_coredumpv(wil_to_dev(wil), fw_dump_data, fw_dump_size, GFP_KERNEL);
	wil_info(wil, "fw core dumped, size %d bytes\n", fw_dump_size);
}