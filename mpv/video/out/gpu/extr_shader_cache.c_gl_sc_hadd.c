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
struct gl_shader_cache {int /*<<< orphan*/  header_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr_xappend0 (struct gl_shader_cache*,int /*<<< orphan*/ *,char const*) ; 

void gl_sc_hadd(struct gl_shader_cache *sc, const char *text)
{
    bstr_xappend0(sc, &sc->header_text, text);
}