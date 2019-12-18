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
struct bstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr_xappend (struct gl_shader_cache*,int /*<<< orphan*/ *,struct bstr) ; 

void gl_sc_hadd_bstr(struct gl_shader_cache *sc, struct bstr text)
{
    bstr_xappend(sc, &sc->header_text, text);
}