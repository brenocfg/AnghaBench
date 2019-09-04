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
struct snd_pcm_substream {int dummy; } ;
struct snd_ice1712 {int /*<<< orphan*/  cs8427; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_cs8427_iec958_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_cs8427(struct snd_ice1712 *ice, struct snd_pcm_substream *substream)
{
	snd_cs8427_iec958_active(ice->cs8427, 0);
}