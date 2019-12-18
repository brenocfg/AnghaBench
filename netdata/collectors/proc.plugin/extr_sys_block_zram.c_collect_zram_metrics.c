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
typedef  int /*<<< orphan*/  ZRAM_DEVICE ;
typedef  int /*<<< orphan*/  DICTIONARY ;

/* Variables and functions */
 int _collect_zram_metrics (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int collect_zram_metrics(char *name, void *entry, void *data) {
    (void)name;
    // collect with calling rrdset_next
    return _collect_zram_metrics(name, (ZRAM_DEVICE *)entry, 1, (DICTIONARY *)data);
}