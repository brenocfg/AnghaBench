#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct swap_map_handle {int /*<<< orphan*/  crc32; int /*<<< orphan*/  first_sector; } ;
struct TYPE_3__ {unsigned int flags; int /*<<< orphan*/  crc32; int /*<<< orphan*/  image; int /*<<< orphan*/  sig; int /*<<< orphan*/  orig_sig; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HIBERNATE_SIG ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  REQ_SYNC ; 
 unsigned int SF_CRC32_MODE ; 
 int hib_submit_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__* swsusp_header ; 
 int /*<<< orphan*/  swsusp_resume_block ; 

__attribute__((used)) static int mark_swapfiles(struct swap_map_handle *handle, unsigned int flags)
{
	int error;

	hib_submit_io(REQ_OP_READ, 0, swsusp_resume_block,
		      swsusp_header, NULL);
	if (!memcmp("SWAP-SPACE",swsusp_header->sig, 10) ||
	    !memcmp("SWAPSPACE2",swsusp_header->sig, 10)) {
		memcpy(swsusp_header->orig_sig,swsusp_header->sig, 10);
		memcpy(swsusp_header->sig, HIBERNATE_SIG, 10);
		swsusp_header->image = handle->first_sector;
		swsusp_header->flags = flags;
		if (flags & SF_CRC32_MODE)
			swsusp_header->crc32 = handle->crc32;
		error = hib_submit_io(REQ_OP_WRITE, REQ_SYNC,
				      swsusp_resume_block, swsusp_header, NULL);
	} else {
		pr_err("Swap header not found!\n");
		error = -ENODEV;
	}
	return error;
}