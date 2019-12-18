#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_2__ {scalar_t__ msg_qbytes; scalar_t__ msg_cbytes; scalar_t__ msg_qnum; } ;
struct msqid_kernel {TYPE_1__ u; } ;
typedef  int collected_number ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int GETSYSCTL_SIMPLE (char*,int*,int) ; 
 int GETSYSCTL_WSIZE (char*,int*,struct msqid_kernel*,int) ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_IPC_MSQ_MESSAGES ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_IPC_MSQ_QUEUES ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_IPC_MSQ_SIZE ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  error (char*) ; 
 struct msqid_kernel* reallocz (struct msqid_kernel*,int) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_kern_ipc_msq(int update_every, usec_t dt) {
    (void)dt;
    static int mib_msgmni[3] = {0, 0, 0};
    struct ipc_msq {
        int msgmni;
        collected_number queues;
        collected_number messages;
        collected_number usedsize;
        collected_number allocsize;
    } ipc_msq = {0, 0, 0, 0, 0};

    if (unlikely(GETSYSCTL_SIMPLE("kern.ipc.msgmni", mib_msgmni, ipc_msq.msgmni))) {
        error("DISABLED: system.ipc_msq_queues chart");
        error("DISABLED: system.ipc_msq_messages chart");
        error("DISABLED: system.ipc_msq_size chart");
        error("DISABLED: kern.ipc.msg module");
        return 1;
    } else {
        static struct msqid_kernel *ipc_msq_data = NULL;
        static int old_msgmni = 0;
        static int mib_msqids[3] = {0, 0, 0};

        if (unlikely(ipc_msq.msgmni != old_msgmni)) {
            ipc_msq_data = reallocz(ipc_msq_data, sizeof(struct msqid_kernel) * ipc_msq.msgmni);
            old_msgmni = ipc_msq.msgmni;
        }
        if (unlikely(
                GETSYSCTL_WSIZE("kern.ipc.msqids", mib_msqids, ipc_msq_data, sizeof(struct msqid_kernel) * ipc_msq.msgmni))) {
            error("DISABLED: system.ipc_msq_queues chart");
            error("DISABLED: system.ipc_msq_messages chart");
            error("DISABLED: system.ipc_msq_size chart");
            error("DISABLED: kern.ipc.msg module");
            return 1;
        } else {
            int i;

            for (i = 0; i < ipc_msq.msgmni; i++) {
                if (unlikely(ipc_msq_data[i].u.msg_qbytes != 0)) {
                    ipc_msq.queues += 1;
                    ipc_msq.messages += ipc_msq_data[i].u.msg_qnum;
                    ipc_msq.usedsize += ipc_msq_data[i].u.msg_cbytes;
                    ipc_msq.allocsize += ipc_msq_data[i].u.msg_qbytes;
                }
            }

            // --------------------------------------------------------------------

            static RRDSET *st_queues = NULL, *st_messages = NULL, *st_size = NULL;
            static RRDDIM *rd_queues = NULL, *rd_messages = NULL, *rd_allocated = NULL, *rd_used = NULL;

            if (unlikely(!st_queues)) {
                st_queues = rrdset_create_localhost(
                        "system",
                        "ipc_msq_queues",
                        NULL,
                        "ipc message queues",
                        NULL,
                        "Number of IPC Message Queues",
                        "queues",
                        "freebsd.plugin",
                        "kern.ipc.msq",
                        NETDATA_CHART_PRIO_SYSTEM_IPC_MSQ_QUEUES,
                        update_every,
                        RRDSET_TYPE_AREA
                );

                rd_queues = rrddim_add(st_queues, "queues", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            }
            else rrdset_next(st_queues);

            rrddim_set_by_pointer(st_queues, rd_queues, ipc_msq.queues);
            rrdset_done(st_queues);

            // --------------------------------------------------------------------

            if (unlikely(!st_messages)) {
                st_messages = rrdset_create_localhost(
                        "system",
                        "ipc_msq_messages",
                        NULL,
                        "ipc message queues",
                        NULL,
                        "Number of Messages in IPC Message Queues",
                        "messages",
                        "freebsd.plugin",
                        "kern.ipc.msq",
                        NETDATA_CHART_PRIO_SYSTEM_IPC_MSQ_MESSAGES,
                        update_every,
                        RRDSET_TYPE_AREA
                );

                rd_messages = rrddim_add(st_messages, "messages", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            }
            else rrdset_next(st_messages);

            rrddim_set_by_pointer(st_messages, rd_messages, ipc_msq.messages);
            rrdset_done(st_messages);

            // --------------------------------------------------------------------

            if (unlikely(!st_size)) {
                st_size = rrdset_create_localhost(
                        "system",
                        "ipc_msq_size",
                        NULL,
                        "ipc message queues",
                        NULL,
                        "Size of IPC Message Queues",
                        "bytes",
                        "freebsd.plugin",
                        "kern.ipc.msq",
                        NETDATA_CHART_PRIO_SYSTEM_IPC_MSQ_SIZE,
                        update_every,
                        RRDSET_TYPE_LINE
                );

                rd_allocated = rrddim_add(st_size, "allocated", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
                rd_used = rrddim_add(st_size, "used", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            }
            else rrdset_next(st_size);

            rrddim_set_by_pointer(st_size, rd_allocated, ipc_msq.allocsize);
            rrddim_set_by_pointer(st_size, rd_used, ipc_msq.usedsize);
            rrdset_done(st_size);
        }
    }

    return 0;
}