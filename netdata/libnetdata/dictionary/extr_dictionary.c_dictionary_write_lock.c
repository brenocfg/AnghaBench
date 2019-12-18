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
struct TYPE_3__ {int /*<<< orphan*/  rwlock; } ;
typedef  TYPE_1__ DICTIONARY ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdata_rwlock_wrlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dictionary_write_lock(DICTIONARY *dict) {
    if(likely(dict->rwlock)) {
        // debug(D_DICTIONARY, "Dictionary WRITE lock");
        netdata_rwlock_wrlock(dict->rwlock);
    }
}