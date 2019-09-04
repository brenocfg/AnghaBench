#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; scalar_t__ len; } ;
typedef  TYPE_1__ pflines ;
typedef  int /*<<< orphan*/  ffline ;

/* Variables and functions */
 size_t PFLINES_INCREASE_STEP ; 
 TYPE_1__* mallocz (int) ; 
 int /*<<< orphan*/  procfile_adaptive_initial_allocation ; 
 size_t procfile_max_words ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline pflines *pflines_new(void) {
    // debug(D_PROCFILE, PF_PREFIX ":   initializing lines");

    size_t size = (unlikely(procfile_adaptive_initial_allocation)) ? procfile_max_words : PFLINES_INCREASE_STEP;

    pflines *new = mallocz(sizeof(pflines) + size * sizeof(ffline));
    new->len = 0;
    new->size = size;
    return new;
}