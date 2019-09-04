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
struct qedi_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  byte; } ;
struct nvm_iscsi_initiator {TYPE_1__ initiator_name; } ;
struct nvm_iscsi_block {struct nvm_iscsi_initiator initiator; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  ISCSI_BOOT_INI_INITIATOR_NAME 128 
 char* NVM_ISCSI_CFG_ISCSI_NAME_MAX_LEN ; 
 struct nvm_iscsi_block* qedi_get_nvram_block (struct qedi_ctx*) ; 
 int sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t qedi_show_boot_ini_info(void *data, int type, char *buf)
{
	struct qedi_ctx *qedi = data;
	struct nvm_iscsi_initiator *initiator;
	int rc;
	struct nvm_iscsi_block *block;

	block = qedi_get_nvram_block(qedi);
	if (!block)
		return 0;

	initiator = &block->initiator;

	switch (type) {
	case ISCSI_BOOT_INI_INITIATOR_NAME:
		rc = sprintf(buf, "%.*s\n", NVM_ISCSI_CFG_ISCSI_NAME_MAX_LEN,
			     initiator->initiator_name.byte);
		break;
	default:
		rc = 0;
		break;
	}
	return rc;
}