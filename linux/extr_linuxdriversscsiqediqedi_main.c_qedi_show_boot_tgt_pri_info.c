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
struct qedi_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_NVM_TGT_PRI ; 
 int /*<<< orphan*/  qedi_show_boot_tgt_info (struct qedi_ctx*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t qedi_show_boot_tgt_pri_info(void *data, int type, char *buf)
{
	struct qedi_ctx *qedi = data;

	return qedi_show_boot_tgt_info(qedi, type, buf, QEDI_NVM_TGT_PRI);
}