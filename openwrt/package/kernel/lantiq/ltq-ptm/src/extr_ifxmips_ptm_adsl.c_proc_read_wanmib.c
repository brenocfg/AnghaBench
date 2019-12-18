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
typedef  int off_t ;
struct TYPE_2__ {int wrx_correct_pdu; int wrx_correct_pdu_bytes; int wrx_tccrc_err_pdu; int wrx_tccrc_err_pdu_bytes; int wrx_ethcrc_err_pdu; int wrx_ethcrc_err_pdu_bytes; int wrx_nodesc_drop_pdu; int wrx_len_violation_drop_pdu; int wrx_idle_bytes; int wrx_nonidle_cw; int wrx_idle_cw; int wrx_err_cw; int wtx_total_pdu; int wtx_total_bytes; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 TYPE_1__* WAN_MIB_TABLE ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int proc_read_wanmib(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    int len = 0;
    int i;
    char *title[] = {
        "dsl0\n",
        "dslfast0\n"
    };

    for ( i = 0; i < ARRAY_SIZE(title); i++ ) {
        len += sprintf(page + off + len, title[i]);
        len += sprintf(page + off + len, "  wrx_correct_pdu            = %d\n", WAN_MIB_TABLE[i].wrx_correct_pdu);
        len += sprintf(page + off + len, "  wrx_correct_pdu_bytes      = %d\n", WAN_MIB_TABLE[i].wrx_correct_pdu_bytes);
        len += sprintf(page + off + len, "  wrx_tccrc_err_pdu          = %d\n", WAN_MIB_TABLE[i].wrx_tccrc_err_pdu);
        len += sprintf(page + off + len, "  wrx_tccrc_err_pdu_bytes    = %d\n", WAN_MIB_TABLE[i].wrx_tccrc_err_pdu_bytes);
        len += sprintf(page + off + len, "  wrx_ethcrc_err_pdu         = %d\n", WAN_MIB_TABLE[i].wrx_ethcrc_err_pdu);
        len += sprintf(page + off + len, "  wrx_ethcrc_err_pdu_bytes   = %d\n", WAN_MIB_TABLE[i].wrx_ethcrc_err_pdu_bytes);
        len += sprintf(page + off + len, "  wrx_nodesc_drop_pdu        = %d\n", WAN_MIB_TABLE[i].wrx_nodesc_drop_pdu);
        len += sprintf(page + off + len, "  wrx_len_violation_drop_pdu = %d\n", WAN_MIB_TABLE[i].wrx_len_violation_drop_pdu);
        len += sprintf(page + off + len, "  wrx_idle_bytes             = %d\n", WAN_MIB_TABLE[i].wrx_idle_bytes);
        len += sprintf(page + off + len, "  wrx_nonidle_cw             = %d\n", WAN_MIB_TABLE[i].wrx_nonidle_cw);
        len += sprintf(page + off + len, "  wrx_idle_cw                = %d\n", WAN_MIB_TABLE[i].wrx_idle_cw);
        len += sprintf(page + off + len, "  wrx_err_cw                 = %d\n", WAN_MIB_TABLE[i].wrx_err_cw);
        len += sprintf(page + off + len, "  wtx_total_pdu              = %d\n", WAN_MIB_TABLE[i].wtx_total_pdu);
        len += sprintf(page + off + len, "  wtx_total_bytes            = %d\n", WAN_MIB_TABLE[i].wtx_total_bytes);
    }

    *eof = 1;

    return len;
}