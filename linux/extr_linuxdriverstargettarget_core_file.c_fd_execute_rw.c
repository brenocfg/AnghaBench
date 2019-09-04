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
struct se_device {int dummy; } ;
struct se_cmd {scalar_t__ data_length; struct se_device* se_dev; } ;
struct scatterlist {int dummy; } ;
struct fd_dev {int fbd_flags; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int FDBD_HAS_ASYNC_IO ; 
 struct fd_dev* FD_DEV (struct se_device*) ; 
 scalar_t__ FD_MAX_BYTES ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  fd_execute_rw_aio (struct se_cmd*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fd_execute_rw_buffered (struct se_cmd*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static sense_reason_t
fd_execute_rw(struct se_cmd *cmd, struct scatterlist *sgl, u32 sgl_nents,
	      enum dma_data_direction data_direction)
{
	struct se_device *dev = cmd->se_dev;
	struct fd_dev *fd_dev = FD_DEV(dev);

	/*
	 * We are currently limited by the number of iovecs (2048) per
	 * single vfs_[writev,readv] call.
	 */
	if (cmd->data_length > FD_MAX_BYTES) {
		pr_err("FILEIO: Not able to process I/O of %u bytes due to"
		       "FD_MAX_BYTES: %u iovec count limitation\n",
			cmd->data_length, FD_MAX_BYTES);
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}

	if (fd_dev->fbd_flags & FDBD_HAS_ASYNC_IO)
		return fd_execute_rw_aio(cmd, sgl, sgl_nents, data_direction);
	return fd_execute_rw_buffered(cmd, sgl, sgl_nents, data_direction);
}