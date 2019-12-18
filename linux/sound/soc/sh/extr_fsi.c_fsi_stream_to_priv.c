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
struct fsi_stream {struct fsi_priv* priv; } ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct fsi_priv *fsi_stream_to_priv(struct fsi_stream *io)
{
	return io->priv;
}