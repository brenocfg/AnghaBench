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
struct snd_ice1712 {int /*<<< orphan*/  cs8427; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_cs8427_iec958_pcm (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_cs8427(struct snd_ice1712 *ice, int rate)
{
	snd_cs8427_iec958_pcm(ice->cs8427, rate);
}