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
struct brcmf_fw_request {int n_items; struct brcmf_fw_item* items; } ;
struct brcmf_fw_item {int /*<<< orphan*/  path; } ;

/* Variables and functions */

__attribute__((used)) static bool brcmf_fw_request_is_valid(struct brcmf_fw_request *req)
{
	struct brcmf_fw_item *item;
	int i;

	if (!req->n_items)
		return false;

	for (i = 0, item = &req->items[0]; i < req->n_items; i++, item++) {
		if (!item->path)
			return false;
	}
	return true;
}