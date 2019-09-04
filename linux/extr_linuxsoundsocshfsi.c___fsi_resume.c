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
struct fsi_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsi_hw_startup (struct fsi_priv*,struct fsi_stream*,struct device*) ; 
 int /*<<< orphan*/  fsi_stream_is_working (struct fsi_priv*,struct fsi_stream*) ; 
 int /*<<< orphan*/  fsi_stream_start (struct fsi_priv*,struct fsi_stream*) ; 

__attribute__((used)) static void __fsi_resume(struct fsi_priv *fsi,
			 struct fsi_stream *io,
			 struct device *dev)
{
	if (!fsi_stream_is_working(fsi, io))
		return;

	fsi_hw_startup(fsi, io, dev);
	fsi_stream_start(fsi, io);
}