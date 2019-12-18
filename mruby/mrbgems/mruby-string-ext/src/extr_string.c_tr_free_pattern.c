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
struct tr_pattern {scalar_t__ flag_on_heap; struct tr_pattern* next; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,struct tr_pattern*) ; 

__attribute__((used)) static inline void
tr_free_pattern(mrb_state *mrb, struct tr_pattern *pat)
{
  while (pat) {
    struct tr_pattern *p = pat->next;
    if (pat->flag_on_heap) {
      mrb_free(mrb, pat);
    }
    pat = p;
  }
}