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
struct lwan_tpl {int /*<<< orphan*/  chunks; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct lwan_tpl*) ; 
 int /*<<< orphan*/  free_chunk_array (int /*<<< orphan*/ *) ; 

void lwan_tpl_free(struct lwan_tpl *tpl)
{
    if (tpl) {
        free_chunk_array(&tpl->chunks);
        free(tpl);
    }
}