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

/* Variables and functions */
 unsigned long long strtoull (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void callback_system_strtoull(void *data1, void *data2) {
    char *string = data1;
    unsigned long long *value = data2;
    *value = strtoull(string, NULL, 10);
}