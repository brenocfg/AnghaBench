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
typedef  int /*<<< orphan*/  u32 ;
struct rsnd_mod {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUF_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_SYS_STATUS0 ; 
 int /*<<< orphan*/  SCU_SYS_STATUS1 ; 
 int /*<<< orphan*/  rsnd_mod_id (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsnd_src_status_clear(struct rsnd_mod *mod)
{
	u32 val = OUF_SRC(rsnd_mod_id(mod));

	rsnd_mod_write(mod, SCU_SYS_STATUS0, val);
	rsnd_mod_write(mod, SCU_SYS_STATUS1, val);
}