#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sc_entry {int /*<<< orphan*/  timer; scalar_t__ pass; int /*<<< orphan*/  ubo; } ;
struct gl_shader_cache {int num_entries; TYPE_2__* ra; struct sc_entry** entries; } ;
struct TYPE_5__ {TYPE_1__* fns; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* renderpass_destroy ) (TYPE_2__*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (struct gl_shader_cache*,char*) ; 
 int /*<<< orphan*/  ra_buf_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  talloc_free (struct sc_entry*) ; 
 int /*<<< orphan*/  timer_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc_flush_cache(struct gl_shader_cache *sc)
{
    MP_DBG(sc, "flushing shader cache\n");

    for (int n = 0; n < sc->num_entries; n++) {
        struct sc_entry *e = sc->entries[n];
        ra_buf_free(sc->ra, &e->ubo);
        if (e->pass)
            sc->ra->fns->renderpass_destroy(sc->ra, e->pass);
        timer_pool_destroy(e->timer);
        talloc_free(e);
    }
    sc->num_entries = 0;
}