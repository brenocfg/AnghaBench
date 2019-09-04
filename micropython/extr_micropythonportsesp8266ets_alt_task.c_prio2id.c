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
typedef  int uint8_t ;

/* Variables and functions */
 int MP_ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int PRIO2ID (int) ; 
 int /*<<< orphan*/  emu_tasks ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static inline int prio2id(uint8_t prio) {
    int id = PRIO2ID(prio);
    if (id < 0 || id >= MP_ARRAY_SIZE(emu_tasks)) {
        printf("task prio out of range: %d\n", prio);
        while (1);
    }
    return id;
}