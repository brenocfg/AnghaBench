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
struct soundscape {TYPE_1__* chip; int /*<<< orphan*/  wss_res; int /*<<< orphan*/  io_res; } ;
struct snd_card {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma1; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 struct soundscape* get_card_soundscape (struct snd_card*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soundscape_free(struct snd_card *c)
{
	struct soundscape *sscape = get_card_soundscape(c);
	release_and_free_resource(sscape->io_res);
	release_and_free_resource(sscape->wss_res);
	free_dma(sscape->chip->dma1);
}