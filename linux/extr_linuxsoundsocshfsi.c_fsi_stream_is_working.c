#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsi_stream {TYPE_1__* substream; } ;
struct fsi_priv {int dummy; } ;
struct fsi_master {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ runtime; } ;

/* Variables and functions */
 struct fsi_master* fsi_get_master (struct fsi_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fsi_stream_is_working(struct fsi_priv *fsi,
				 struct fsi_stream *io)
{
	struct fsi_master *master = fsi_get_master(fsi);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&master->lock, flags);
	ret = !!(io->substream && io->substream->runtime);
	spin_unlock_irqrestore(&master->lock, flags);

	return ret;
}