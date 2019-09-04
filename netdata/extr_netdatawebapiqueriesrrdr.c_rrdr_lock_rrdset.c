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
struct TYPE_3__ {int has_st_lock; int /*<<< orphan*/  st; } ;
typedef  TYPE_1__ RRDR ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  rrdset_rdlock (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) inline static void rrdr_lock_rrdset(RRDR *r) {
    if(unlikely(!r)) {
        error("NULL value given!");
        return;
    }

    rrdset_rdlock(r->st);
    r->has_st_lock = 1;
}