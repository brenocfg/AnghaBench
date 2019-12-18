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
struct gl_shader_cache {int num_exts; int /*<<< orphan*/ * exts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct gl_shader_cache*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  talloc_strdup (struct gl_shader_cache*,char*) ; 

void gl_sc_enable_extension(struct gl_shader_cache *sc, char *name)
{
    for (int n = 0; n < sc->num_exts; n++) {
        if (strcmp(sc->exts[n], name) == 0)
            return;
    }
    MP_TARRAY_APPEND(sc, sc->exts, sc->num_exts, talloc_strdup(sc, name));
}