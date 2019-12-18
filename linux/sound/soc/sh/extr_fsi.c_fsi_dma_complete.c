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
struct fsi_stream {int /*<<< orphan*/  period_samples; } ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsi_count_fifo_err (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_pointer_update (struct fsi_stream*,int /*<<< orphan*/ ) ; 
 struct fsi_priv* fsi_stream_to_priv (struct fsi_stream*) ; 

__attribute__((used)) static void fsi_dma_complete(void *data)
{
	struct fsi_stream *io = (struct fsi_stream *)data;
	struct fsi_priv *fsi = fsi_stream_to_priv(io);

	fsi_pointer_update(io, io->period_samples);

	fsi_count_fifo_err(fsi);
}