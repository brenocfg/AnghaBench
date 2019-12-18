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
struct snd_galaxy {int /*<<< orphan*/  res_port; scalar_t__ port; int /*<<< orphan*/  res_config_port; scalar_t__ config_port; int /*<<< orphan*/  config; int /*<<< orphan*/  res_wss_port; scalar_t__ wss_port; } ;
struct snd_card {struct snd_galaxy* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  galaxy_set_config (struct snd_galaxy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioport_unmap (scalar_t__) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wss_set_config (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_galaxy_free(struct snd_card *card)
{
	struct snd_galaxy *galaxy = card->private_data;

	if (galaxy->wss_port) {
		wss_set_config(galaxy->wss_port, 0);
		ioport_unmap(galaxy->wss_port);
		release_and_free_resource(galaxy->res_wss_port);
	}
	if (galaxy->config_port) {
		galaxy_set_config(galaxy, galaxy->config);
		ioport_unmap(galaxy->config_port);
		release_and_free_resource(galaxy->res_config_port);
	}
	if (galaxy->port) {
		ioport_unmap(galaxy->port);
		release_and_free_resource(galaxy->res_port);
	}
}