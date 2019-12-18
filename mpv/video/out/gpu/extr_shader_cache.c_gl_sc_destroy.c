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
struct gl_shader_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_sc_reset (struct gl_shader_cache*) ; 
 int /*<<< orphan*/  sc_flush_cache (struct gl_shader_cache*) ; 
 int /*<<< orphan*/  talloc_free (struct gl_shader_cache*) ; 

void gl_sc_destroy(struct gl_shader_cache *sc)
{
    if (!sc)
        return;
    gl_sc_reset(sc);
    sc_flush_cache(sc);
    talloc_free(sc);
}