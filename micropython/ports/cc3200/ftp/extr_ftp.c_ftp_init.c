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
struct TYPE_2__ {int c_sd; int d_sd; int lc_sd; int ld_sd; int special_file; scalar_t__ volcount; int /*<<< orphan*/  substate; int /*<<< orphan*/  state; int /*<<< orphan*/  e_open; int /*<<< orphan*/ * dBuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FTP_NOTHING_OPEN ; 
 int /*<<< orphan*/  E_FTP_STE_DISABLED ; 
 int /*<<< orphan*/  E_FTP_STE_SUB_DISCONNECTED ; 
 scalar_t__ FTP_BUFFER_SIZE ; 
 scalar_t__ FTP_CMD_SIZE_MAX ; 
 scalar_t__ FTP_MAX_PARAM_SIZE ; 
 int /*<<< orphan*/  FTP_SOCKETFIFO_ELEMENTS_MAX ; 
 int /*<<< orphan*/  SOCKETFIFO_Init (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ftp_cmd_buffer ; 
 TYPE_1__ ftp_data ; 
 scalar_t__ ftp_fifoelements ; 
 int /*<<< orphan*/ * ftp_path ; 
 int /*<<< orphan*/ * ftp_scratch_buffer ; 
 int /*<<< orphan*/  ftp_socketfifo ; 
 void* mem_Malloc (scalar_t__) ; 

void ftp_init (void) {
    // Allocate memory for the data buffer, and the file system structs (from the RTOS heap)
    ASSERT ((ftp_data.dBuffer = mem_Malloc(FTP_BUFFER_SIZE)) != NULL);
    ASSERT ((ftp_path = mem_Malloc(FTP_MAX_PARAM_SIZE)) != NULL);
    ASSERT ((ftp_scratch_buffer = mem_Malloc(FTP_MAX_PARAM_SIZE)) != NULL);
    ASSERT ((ftp_cmd_buffer = mem_Malloc(FTP_MAX_PARAM_SIZE + FTP_CMD_SIZE_MAX)) != NULL);
    SOCKETFIFO_Init (&ftp_socketfifo, (void *)ftp_fifoelements, FTP_SOCKETFIFO_ELEMENTS_MAX);
    ftp_data.c_sd  = -1;
    ftp_data.d_sd  = -1;
    ftp_data.lc_sd = -1;
    ftp_data.ld_sd = -1;
    ftp_data.e_open = E_FTP_NOTHING_OPEN;
    ftp_data.state = E_FTP_STE_DISABLED;
    ftp_data.substate = E_FTP_STE_SUB_DISCONNECTED;
    ftp_data.special_file = false;
    ftp_data.volcount = 0;
}