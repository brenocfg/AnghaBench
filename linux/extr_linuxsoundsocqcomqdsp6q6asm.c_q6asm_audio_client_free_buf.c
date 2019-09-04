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
struct audio_port_data {int /*<<< orphan*/ * buf; scalar_t__ num_periods; } ;
struct audio_client {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void q6asm_audio_client_free_buf(struct audio_client *ac,
					struct audio_port_data *port)
{
	unsigned long flags;

	spin_lock_irqsave(&ac->lock, flags);
	port->num_periods = 0;
	kfree(port->buf);
	port->buf = NULL;
	spin_unlock_irqrestore(&ac->lock, flags);
}