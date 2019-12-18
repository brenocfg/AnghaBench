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

/* Variables and functions */
 int EIO ; 
 int fsi_stream_handler_call (struct fsi_stream*,int /*<<< orphan*/ ,struct fsi_priv*,struct fsi_stream*) ; 
 struct fsi_priv* fsi_stream_to_priv (struct fsi_stream*) ; 
 int /*<<< orphan*/  transfer ; 

__attribute__((used)) static int fsi_stream_transfer(struct fsi_stream *io)
{
	struct fsi_priv *fsi = fsi_stream_to_priv(io);
	if (!fsi)
		return -EIO;

	return fsi_stream_handler_call(io, transfer, fsi, io);
}