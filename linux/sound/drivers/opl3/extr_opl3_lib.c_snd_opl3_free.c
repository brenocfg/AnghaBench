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
struct snd_opl3 {int /*<<< orphan*/  res_r_port; int /*<<< orphan*/  res_l_port; int /*<<< orphan*/  (* private_free ) (struct snd_opl3*) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  kfree (struct snd_opl3*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_opl3_clear_patches (struct snd_opl3*) ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*) ; 

__attribute__((used)) static int snd_opl3_free(struct snd_opl3 *opl3)
{
	if (snd_BUG_ON(!opl3))
		return -ENXIO;
	if (opl3->private_free)
		opl3->private_free(opl3);
	snd_opl3_clear_patches(opl3);
	release_and_free_resource(opl3->res_l_port);
	release_and_free_resource(opl3->res_r_port);
	kfree(opl3);
	return 0;
}