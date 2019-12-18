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
struct snd_rme9652 {int /*<<< orphan*/  playback_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RME9652_DMA_AREA_BYTES ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rme9652_silence_playback(struct snd_rme9652 *rme9652)
{
	memset(rme9652->playback_buffer, 0, RME9652_DMA_AREA_BYTES);
}