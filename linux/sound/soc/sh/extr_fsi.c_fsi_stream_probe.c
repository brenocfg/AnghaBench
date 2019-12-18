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
struct fsi_stream {int dummy; } ;
struct fsi_priv {struct fsi_stream capture; struct fsi_stream playback; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int fsi_stream_handler_call (struct fsi_stream*,int /*<<< orphan*/ ,struct fsi_priv*,struct fsi_stream*,struct device*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int fsi_stream_probe(struct fsi_priv *fsi, struct device *dev)
{
	struct fsi_stream *io;
	int ret1, ret2;

	io = &fsi->playback;
	ret1 = fsi_stream_handler_call(io, probe, fsi, io, dev);

	io = &fsi->capture;
	ret2 = fsi_stream_handler_call(io, probe, fsi, io, dev);

	if (ret1 < 0)
		return ret1;
	if (ret2 < 0)
		return ret2;

	return 0;
}