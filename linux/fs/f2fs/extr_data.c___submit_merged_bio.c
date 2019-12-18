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
struct f2fs_io_info {int /*<<< orphan*/  type; int /*<<< orphan*/  op; int /*<<< orphan*/  op_flags; } ;
struct f2fs_bio_info {int /*<<< orphan*/ * bio; TYPE_1__* sbi; struct f2fs_io_info fio; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __submit_bio (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_read_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_prepare_read_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_f2fs_prepare_write_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __submit_merged_bio(struct f2fs_bio_info *io)
{
	struct f2fs_io_info *fio = &io->fio;

	if (!io->bio)
		return;

	bio_set_op_attrs(io->bio, fio->op, fio->op_flags);

	if (is_read_io(fio->op))
		trace_f2fs_prepare_read_bio(io->sbi->sb, fio->type, io->bio);
	else
		trace_f2fs_prepare_write_bio(io->sbi->sb, fio->type, io->bio);

	__submit_bio(io->sbi, io->bio, fio->type);
	io->bio = NULL;
}