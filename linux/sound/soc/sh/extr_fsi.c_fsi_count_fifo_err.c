#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  uerr_num; int /*<<< orphan*/  oerr_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  uerr_num; int /*<<< orphan*/  oerr_num; } ;
struct fsi_priv {TYPE_2__ capture; TYPE_1__ playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_ST ; 
 int /*<<< orphan*/  DOFF_ST ; 
 int ERR_OVER ; 
 int ERR_UNDER ; 
 int fsi_reg_read (struct fsi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_reg_write (struct fsi_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsi_count_fifo_err(struct fsi_priv *fsi)
{
	u32 ostatus = fsi_reg_read(fsi, DOFF_ST);
	u32 istatus = fsi_reg_read(fsi, DIFF_ST);

	if (ostatus & ERR_OVER)
		fsi->playback.oerr_num++;

	if (ostatus & ERR_UNDER)
		fsi->playback.uerr_num++;

	if (istatus & ERR_OVER)
		fsi->capture.oerr_num++;

	if (istatus & ERR_UNDER)
		fsi->capture.uerr_num++;

	fsi_reg_write(fsi, DOFF_ST, 0);
	fsi_reg_write(fsi, DIFF_ST, 0);
}