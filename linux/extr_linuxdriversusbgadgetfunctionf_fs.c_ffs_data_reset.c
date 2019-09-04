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
struct TYPE_2__ {scalar_t__ count; } ;
struct ffs_data {scalar_t__ flags; int /*<<< orphan*/  setup_state; int /*<<< orphan*/  state; TYPE_1__ ev; scalar_t__ eps_count; scalar_t__ interfaces_count; scalar_t__ strings_count; scalar_t__ ss_descs_count; scalar_t__ hs_descs_count; scalar_t__ fs_descs_count; scalar_t__ raw_descs_length; int /*<<< orphan*/ * stringtabs; int /*<<< orphan*/ * raw_strings; int /*<<< orphan*/ * raw_descs; int /*<<< orphan*/ * raw_descs_data; int /*<<< orphan*/ * epfiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  FFS_NO_SETUP ; 
 int /*<<< orphan*/  FFS_READ_DESCRIPTORS ; 
 int /*<<< orphan*/  ffs_data_clear (struct ffs_data*) ; 

__attribute__((used)) static void ffs_data_reset(struct ffs_data *ffs)
{
	ENTER();

	ffs_data_clear(ffs);

	ffs->epfiles = NULL;
	ffs->raw_descs_data = NULL;
	ffs->raw_descs = NULL;
	ffs->raw_strings = NULL;
	ffs->stringtabs = NULL;

	ffs->raw_descs_length = 0;
	ffs->fs_descs_count = 0;
	ffs->hs_descs_count = 0;
	ffs->ss_descs_count = 0;

	ffs->strings_count = 0;
	ffs->interfaces_count = 0;
	ffs->eps_count = 0;

	ffs->ev.count = 0;

	ffs->state = FFS_READ_DESCRIPTORS;
	ffs->setup_state = FFS_NO_SETUP;
	ffs->flags = 0;
}