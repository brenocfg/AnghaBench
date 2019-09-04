#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct window_global {int dummy; } ;
struct window_data {int dummy; } ;
struct settings {int slab_automove_window; double slab_automove_ratio; int /*<<< orphan*/  ext_item_size; int /*<<< orphan*/  slab_automove_freeratio; } ;
struct TYPE_3__ {int window_size; double max_age_ratio; int pool_filled_once; int /*<<< orphan*/  sam_before; int /*<<< orphan*/  iam_before; struct TYPE_3__* window_global; struct TYPE_3__* window_data; struct settings* settings; scalar_t__ last_memcheck_run; int /*<<< orphan*/  item_size; int /*<<< orphan*/  free_ratio; } ;
typedef  TYPE_1__ slab_automove ;

/* Variables and functions */
 int MAX_NUMBER_OF_SLAB_CLASSES ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  fill_item_stats_automove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_slab_stats_automove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void *slab_automove_extstore_init(struct settings *settings) {
    uint32_t window_size = settings->slab_automove_window;
    double max_age_ratio = settings->slab_automove_ratio;
    slab_automove *a = calloc(1, sizeof(slab_automove));
    if (a == NULL)
        return NULL;
    a->window_data = calloc(window_size * MAX_NUMBER_OF_SLAB_CLASSES, sizeof(struct window_data));
    a->window_global = calloc(window_size, sizeof(struct window_global));
    a->window_size = window_size;
    a->max_age_ratio = max_age_ratio;
    a->free_ratio = settings->slab_automove_freeratio;
    a->item_size = settings->ext_item_size;
    a->last_memcheck_run = 0;
    a->settings = settings;
    a->pool_filled_once = false;
    if (a->window_data == NULL || a->window_global == NULL) {
        if (a->window_data)
            free(a->window_data);
        if (a->window_global)
            free(a->window_global);
        free(a);
        return NULL;
    }

    // do a dry run to fill the before structs
    fill_item_stats_automove(a->iam_before);
    fill_slab_stats_automove(a->sam_before);

    return (void *)a;
}