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
struct snd_midi_event {int /*<<< orphan*/  type; scalar_t__ qlen; scalar_t__ read; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_INVALID ; 

__attribute__((used)) static inline void reset_encode(struct snd_midi_event *dev)
{
	dev->read = 0;
	dev->qlen = 0;
	dev->type = ST_INVALID;
}