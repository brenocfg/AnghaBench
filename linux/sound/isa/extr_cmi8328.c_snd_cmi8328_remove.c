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
struct snd_cmi8328 {int /*<<< orphan*/  port; scalar_t__ gameport; } ;
struct snd_card {struct snd_cmi8328* private_data; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG1 ; 
 int /*<<< orphan*/  CFG1_SB_DISABLE ; 
 int /*<<< orphan*/  CFG2 ; 
 int /*<<< orphan*/  CFG3 ; 
 struct snd_card* dev_get_drvdata (struct device*) ; 
 struct resource* gameport_get_port_data (scalar_t__) ; 
 int /*<<< orphan*/  gameport_unregister_port (scalar_t__) ; 
 int /*<<< orphan*/  release_and_free_resource (struct resource*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int /*<<< orphan*/  snd_cmi8328_cfg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cmi8328_remove(struct device *pdev, unsigned int dev)
{
	struct snd_card *card = dev_get_drvdata(pdev);
	struct snd_cmi8328 *cmi = card->private_data;

#ifdef SUPPORT_JOYSTICK
	if (cmi->gameport) {
		struct resource *res = gameport_get_port_data(cmi->gameport);
		gameport_unregister_port(cmi->gameport);
		release_and_free_resource(res);
	}
#endif
	/* disable everything */
	snd_cmi8328_cfg_write(cmi->port, CFG1, CFG1_SB_DISABLE);
	snd_cmi8328_cfg_write(cmi->port, CFG2, 0);
	snd_cmi8328_cfg_write(cmi->port, CFG3, 0);
	snd_card_free(card);
	return 0;
}