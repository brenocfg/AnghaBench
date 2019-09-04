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
struct dk_cxlflash_uvirtual {int /*<<< orphan*/  last_lba; int /*<<< orphan*/  lun_size; int /*<<< orphan*/  rsrc_handle; int /*<<< orphan*/  context_id; int /*<<< orphan*/  hdr; } ;
struct dk_cxlflash_resize {int /*<<< orphan*/  last_lba; int /*<<< orphan*/  req_size; int /*<<< orphan*/  rsrc_handle; int /*<<< orphan*/  context_id; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */

__attribute__((used)) static void marshal_virt_to_resize(struct dk_cxlflash_uvirtual *virt,
				   struct dk_cxlflash_resize *resize)
{
	resize->hdr = virt->hdr;
	resize->context_id = virt->context_id;
	resize->rsrc_handle = virt->rsrc_handle;
	resize->req_size = virt->lun_size;
	resize->last_lba = virt->last_lba;
}