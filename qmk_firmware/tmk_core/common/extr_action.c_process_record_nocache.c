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
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 int disable_action_cache ; 
 int /*<<< orphan*/  process_record (int /*<<< orphan*/ *) ; 

void process_record_nocache(keyrecord_t *record) {
    disable_action_cache = true;
    process_record(record);
    disable_action_cache = false;
}