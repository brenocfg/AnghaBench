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
struct fsi_priv {struct fsi_stream playback; } ;

/* Variables and functions */

__attribute__((used)) static inline int fsi_stream_is_play(struct fsi_priv *fsi,
				     struct fsi_stream *io)
{
	return &fsi->playback == io;
}