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
struct fsi_stream {int /*<<< orphan*/ * chan; } ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsi_stream_stop (struct fsi_priv*,struct fsi_stream*) ; 

__attribute__((used)) static int fsi_dma_remove(struct fsi_priv *fsi, struct fsi_stream *io)
{
	fsi_stream_stop(fsi, io);

	if (io->chan)
		dma_release_channel(io->chan);

	io->chan = NULL;
	return 0;
}