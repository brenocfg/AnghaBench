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
struct gl_shader_cache {int next_uniform_dynamic; } ;

/* Variables and functions */

void gl_sc_uniform_dynamic(struct gl_shader_cache *sc)
{
    sc->next_uniform_dynamic = true;
}