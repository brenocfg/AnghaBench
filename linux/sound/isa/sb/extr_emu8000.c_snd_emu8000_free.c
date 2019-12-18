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
struct snd_emu8000 {int /*<<< orphan*/  res_port3; int /*<<< orphan*/  res_port2; int /*<<< orphan*/  res_port1; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_emu8000*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_emu8000_free(struct snd_emu8000 *hw)
{
	release_and_free_resource(hw->res_port1);
	release_and_free_resource(hw->res_port2);
	release_and_free_resource(hw->res_port3);
	kfree(hw);
	return 0;
}