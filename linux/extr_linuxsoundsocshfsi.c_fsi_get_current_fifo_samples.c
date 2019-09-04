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
typedef  int u32 ;
struct fsi_stream {int dummy; } ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_ST ; 
 int /*<<< orphan*/  DOFF_ST ; 
 int fsi_frame2sample (struct fsi_priv*,int) ; 
 int fsi_reg_read (struct fsi_priv*,int /*<<< orphan*/ ) ; 
 int fsi_stream_is_play (struct fsi_priv*,struct fsi_stream*) ; 

__attribute__((used)) static int fsi_get_current_fifo_samples(struct fsi_priv *fsi,
					struct fsi_stream *io)
{
	int is_play = fsi_stream_is_play(fsi, io);
	u32 status;
	int frames;

	status = is_play ?
		fsi_reg_read(fsi, DOFF_ST) :
		fsi_reg_read(fsi, DIFF_ST);

	frames = 0x1ff & (status >> 8);

	return fsi_frame2sample(fsi, frames);
}