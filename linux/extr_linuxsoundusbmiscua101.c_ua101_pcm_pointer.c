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
struct ua101_stream {unsigned int buffer_pos; } ;
struct ua101 {int /*<<< orphan*/  lock; } ;
typedef  unsigned int snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline snd_pcm_uframes_t ua101_pcm_pointer(struct ua101 *ua,
						  struct ua101_stream *stream)
{
	unsigned long flags;
	unsigned int pos;

	spin_lock_irqsave(&ua->lock, flags);
	pos = stream->buffer_pos;
	spin_unlock_irqrestore(&ua->lock, flags);
	return pos;
}