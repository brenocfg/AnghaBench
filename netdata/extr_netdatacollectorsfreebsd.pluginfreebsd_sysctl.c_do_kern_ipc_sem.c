#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_3__ {int mode; } ;
struct TYPE_4__ {scalar_t__ sem_nsems; TYPE_1__ sem_perm; } ;
struct semid_kernel {TYPE_2__ u; } ;
typedef  int collected_number ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int GETSYSCTL_SIMPLE (char*,int*,int) ; 
 int GETSYSCTL_WSIZE (char*,int*,struct semid_kernel*,int) ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_IPC_SEMAPHORES ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_IPC_SEM_ARRAYS ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int SEM_ALLOC ; 
 int /*<<< orphan*/  error (char*) ; 
 struct semid_kernel* reallocz (struct semid_kernel*,int) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_kern_ipc_sem(int update_every, usec_t dt) {
    (void)dt;
    static int mib_semmni[3] = {0, 0, 0};
    struct ipc_sem {
        int semmni;
        collected_number sets;
        collected_number semaphores;
    } ipc_sem = {0, 0, 0};

    if (unlikely(GETSYSCTL_SIMPLE("kern.ipc.semmni", mib_semmni, ipc_sem.semmni))) {
        error("DISABLED: system.ipc_semaphores chart");
        error("DISABLED: system.ipc_semaphore_arrays chart");
        error("DISABLED: kern.ipc.sem module");
        return 1;
    } else {
        static struct semid_kernel *ipc_sem_data = NULL;
        static int old_semmni = 0;
        static int mib_sema[3] = {0, 0, 0};

        if (unlikely(ipc_sem.semmni != old_semmni)) {
            ipc_sem_data = reallocz(ipc_sem_data, sizeof(struct semid_kernel) * ipc_sem.semmni);
            old_semmni = ipc_sem.semmni;
        }
        if (unlikely(GETSYSCTL_WSIZE("kern.ipc.sema", mib_sema, ipc_sem_data, sizeof(struct semid_kernel) * ipc_sem.semmni))) {
            error("DISABLED: system.ipc_semaphores chart");
            error("DISABLED: system.ipc_semaphore_arrays chart");
            error("DISABLED: kern.ipc.sem module");
            return 1;
        } else {
            int i;

            for (i = 0; i < ipc_sem.semmni; i++) {
                if (unlikely(ipc_sem_data[i].u.sem_perm.mode & SEM_ALLOC)) {
                    ipc_sem.sets += 1;
                    ipc_sem.semaphores += ipc_sem_data[i].u.sem_nsems;
                }
            }

            // --------------------------------------------------------------------

            static RRDSET *st_semaphores = NULL, *st_semaphore_arrays = NULL;
            static RRDDIM *rd_semaphores = NULL, *rd_semaphore_arrays = NULL;

            if (unlikely(!st_semaphores)) {
                st_semaphores = rrdset_create_localhost(
                        "system",
                        "ipc_semaphores",
                        NULL,
                        "ipc semaphores",
                        NULL,
                        "IPC Semaphores",
                        "semaphores",
                        "freebsd.plugin",
                        "kern.ipc.sem",
                        NETDATA_CHART_PRIO_SYSTEM_IPC_SEMAPHORES,
                        update_every,
                        RRDSET_TYPE_AREA
                );

                rd_semaphores = rrddim_add(st_semaphores, "semaphores", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            }
            else rrdset_next(st_semaphores);

            rrddim_set_by_pointer(st_semaphores, rd_semaphores, ipc_sem.semaphores);
            rrdset_done(st_semaphores);

            // --------------------------------------------------------------------

            if (unlikely(!st_semaphore_arrays)) {
                st_semaphore_arrays = rrdset_create_localhost(
                        "system",
                        "ipc_semaphore_arrays",
                        NULL,
                        "ipc semaphores",
                        NULL,
                        "IPC Semaphore Arrays",
                        "arrays",
                        "freebsd.plugin",
                        "kern.ipc.sem",
                        NETDATA_CHART_PRIO_SYSTEM_IPC_SEM_ARRAYS,
                        update_every,
                        RRDSET_TYPE_AREA
                );

                rd_semaphore_arrays = rrddim_add(st_semaphore_arrays, "arrays", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            }
            else rrdset_next(st_semaphore_arrays);

            rrddim_set_by_pointer(st_semaphore_arrays, rd_semaphore_arrays, ipc_sem.sets);
            rrdset_done(st_semaphore_arrays);
        }
    }

    return 0;
}