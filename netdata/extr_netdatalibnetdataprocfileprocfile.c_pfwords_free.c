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
typedef  int /*<<< orphan*/  pfwords ;

/* Variables and functions */
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pfwords_free(pfwords *fw) {
    // debug(D_PROCFILE, PF_PREFIX ":   freeing words");

    freez(fw);
}