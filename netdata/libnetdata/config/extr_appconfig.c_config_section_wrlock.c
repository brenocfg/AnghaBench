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
struct section {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdata_mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void config_section_wrlock(struct section *co) {
    netdata_mutex_lock(&co->mutex);
}