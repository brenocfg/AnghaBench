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
struct cEnv_t {int /*<<< orphan*/  TRIPLET; int /*<<< orphan*/  SHDR; int /*<<< orphan*/  LDFLAGS; int /*<<< orphan*/  CFLAGS; int /*<<< orphan*/  CC; int /*<<< orphan*/  SFLIBPATH; } ;

/* Variables and functions */

__attribute__((used)) static inline bool r_egg_Cfile_check_cEnv(struct cEnv_t *cEnv) {
	return (!cEnv->SFLIBPATH || !cEnv->CC || !cEnv->CFLAGS || !cEnv->LDFLAGS
		|| !cEnv->SHDR || !cEnv->TRIPLET);
}