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
struct key_source {scalar_t__ random2; scalar_t__ random1; scalar_t__ pre_master; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SHOW_KEY_SOURCE ; 
 int /*<<< orphan*/  VALGRIND_MAKE_READABLE (void*,int) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_hex (scalar_t__,int,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 

__attribute__((used)) static void
key_source_print(const struct key_source *k,
                 const char *prefix)
{
    struct gc_arena gc = gc_new();

    VALGRIND_MAKE_READABLE((void *)k->pre_master, sizeof(k->pre_master));
    VALGRIND_MAKE_READABLE((void *)k->random1, sizeof(k->random1));
    VALGRIND_MAKE_READABLE((void *)k->random2, sizeof(k->random2));

    dmsg(D_SHOW_KEY_SOURCE,
         "%s pre_master: %s",
         prefix,
         format_hex(k->pre_master, sizeof(k->pre_master), 0, &gc));
    dmsg(D_SHOW_KEY_SOURCE,
         "%s random1: %s",
         prefix,
         format_hex(k->random1, sizeof(k->random1), 0, &gc));
    dmsg(D_SHOW_KEY_SOURCE,
         "%s random2: %s",
         prefix,
         format_hex(k->random2, sizeof(k->random2), 0, &gc));

    gc_free(&gc);
}