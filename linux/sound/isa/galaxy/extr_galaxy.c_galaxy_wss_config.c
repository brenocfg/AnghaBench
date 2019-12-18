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
typedef  int /*<<< orphan*/  u8 ;
struct snd_galaxy {int /*<<< orphan*/  wss_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GALAXY_MODE_WSS ; 
 int galaxy_set_mode (struct snd_galaxy*,int /*<<< orphan*/ ) ; 
 int wss_detect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wss_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int galaxy_wss_config(struct snd_galaxy *galaxy, u8 wss_config)
{
	int err;

	err = wss_detect(galaxy->wss_port);
	if (err < 0)
		return err;

	wss_set_config(galaxy->wss_port, wss_config);

	err = galaxy_set_mode(galaxy, GALAXY_MODE_WSS);
	if (err < 0)
		return err;

	return 0;
}