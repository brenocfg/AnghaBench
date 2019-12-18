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
typedef  enum reg_name { ____Placeholder_reg_name } reg_name ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_2__ {scalar_t__ Thread; } ;
typedef  int /*<<< orphan*/ * PETHREAD ;
typedef  int /*<<< orphan*/  KDSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentContext ; 
 TYPE_1__ CurrentStateChange ; 
 int /*<<< orphan*/  KDDBGPRINT (char*) ; 
 scalar_t__ PsGetThreadId (int /*<<< orphan*/ *) ; 
 void* ctx_to_reg (int /*<<< orphan*/ *,int,unsigned short*) ; 
 int /*<<< orphan*/ * find_thread (scalar_t__,scalar_t__) ; 
 scalar_t__ gdb_dbg_pid ; 
 scalar_t__ gdb_dbg_tid ; 
 int /*<<< orphan*/ * gdb_input ; 
 scalar_t__ gdb_tid_to_handle (scalar_t__) ; 
 int hex_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_gdb_memory (void*,unsigned short) ; 
 int /*<<< orphan*/  send_gdb_packet (char*) ; 
 void* thread_to_reg (int /*<<< orphan*/ *,int,unsigned short*) ; 

KDSTATUS
gdb_send_register(void)
{
    enum reg_name reg_name;
    void *ptr;
    unsigned short size;

    /* Get the GDB register name (gdb_input = "pXX") */
    reg_name = (hex_value(gdb_input[1]) << 4) | hex_value(gdb_input[2]);

    if (((gdb_dbg_pid == 0) && (gdb_dbg_tid == 0)) ||
            gdb_tid_to_handle(gdb_dbg_tid) == PsGetThreadId((PETHREAD)(ULONG_PTR)CurrentStateChange.Thread))
    {
        /* We can get it from the context of the current exception */
        ptr = ctx_to_reg(&CurrentContext, reg_name, &size);
    }
    else
    {
        PETHREAD DbgThread;

        DbgThread = find_thread(gdb_dbg_pid, gdb_dbg_tid);

        if (DbgThread == NULL)
        {
            /* Thread is dead */
            return send_gdb_packet("E03");
        }

        ptr = thread_to_reg(DbgThread, reg_name, &size);
    }

    if (!ptr)
    {
        /* Undefined. Let's assume 32 bit register */
        return send_gdb_packet("xxxxxxxx");
    }
    else
    {
        KDDBGPRINT("KDDBG : Sending registers as memory.\n");
        return send_gdb_memory(ptr, size);
    }
}