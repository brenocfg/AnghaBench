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
typedef  int /*<<< orphan*/  ushort ;
union semun {int /*<<< orphan*/ * array; } ;
struct seminfo {int /*<<< orphan*/  semaem; int /*<<< orphan*/  semusz; } ;
struct ipc_status {int /*<<< orphan*/  semaem; int /*<<< orphan*/  semusz; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEM_INFO ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ semctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union semun) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int ipc_sem_get_status(struct ipc_status *st) {
    struct seminfo seminfo;
    union semun arg;

    arg.array = (ushort *)  (void *) &seminfo;

    if(unlikely(semctl (0, 0, SEM_INFO, arg) < 0)) {
        /* kernel not configured for semaphores */
        static int error_shown = 0;
        if(unlikely(!error_shown)) {
            error("IPC: kernel is not configured for semaphores");
            error_shown = 1;
        }
        st->semusz = 0;
        st->semaem = 0;
        return -1;
    }

    st->semusz = seminfo.semusz;
    st->semaem = seminfo.semaem;
    return 0;
}