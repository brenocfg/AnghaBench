#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* words; TYPE_3__* lines; } ;
typedef  TYPE_2__ procfile ;
struct TYPE_10__ {int len; int size; TYPE_4__* lines; } ;
typedef  TYPE_3__ pflines ;
struct TYPE_11__ {size_t words; int /*<<< orphan*/  first; } ;
typedef  TYPE_4__ ffline ;
struct TYPE_8__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int PFLINES_INCREASE_STEP ; 
 TYPE_3__* reallocz (TYPE_3__*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline size_t *pflines_add(procfile *ff) {
    // debug(D_PROCFILE, PF_PREFIX ":   adding line %d at word %d", fl->len, first_word);

    pflines *fl = ff->lines;
    if(unlikely(fl->len == fl->size)) {
        // debug(D_PROCFILE, PF_PREFIX ":   expanding lines");

        ff->lines = fl = reallocz(fl, sizeof(pflines) + (fl->size + PFLINES_INCREASE_STEP) * sizeof(ffline));
        fl->size += PFLINES_INCREASE_STEP;
    }

    ffline *ffl = &fl->lines[fl->len++];
    ffl->words = 0;
    ffl->first = ff->words->len;

    return &ffl->words;
}