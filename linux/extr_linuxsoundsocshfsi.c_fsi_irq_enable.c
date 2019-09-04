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
struct fsi_stream {int dummy; } ;
struct fsi_priv {int dummy; } ;
struct fsi_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB_IO (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_core_mask_set (struct fsi_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsi_master* fsi_get_master (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_get_port_shift (struct fsi_priv*,struct fsi_stream*) ; 
 int /*<<< orphan*/  iemsk ; 
 int /*<<< orphan*/  imsk ; 

__attribute__((used)) static void fsi_irq_enable(struct fsi_priv *fsi, struct fsi_stream *io)
{
	u32 data = AB_IO(1, fsi_get_port_shift(fsi, io));
	struct fsi_master *master = fsi_get_master(fsi);

	fsi_core_mask_set(master, imsk,  data, data);
	fsi_core_mask_set(master, iemsk, data, data);
}