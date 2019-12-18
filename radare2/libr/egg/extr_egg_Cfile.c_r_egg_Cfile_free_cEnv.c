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
struct cEnv_t {struct cEnv_t* TRIPLET; struct cEnv_t* SHDR; struct cEnv_t* LDFLAGS; struct cEnv_t* CFLAGS; struct cEnv_t* CC; struct cEnv_t* SFLIBPATH; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cEnv_t*) ; 

__attribute__((used)) static void r_egg_Cfile_free_cEnv(struct cEnv_t *cEnv) {
	if (cEnv) {
		free (cEnv->SFLIBPATH);
		free (cEnv->CC);
		free (cEnv->CFLAGS);
		free (cEnv->LDFLAGS);
		free (cEnv->SHDR);
		free (cEnv->TRIPLET);
	}
	free (cEnv);
}