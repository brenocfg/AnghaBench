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
struct nci_mode_set_cmd {int mode; int /*<<< orphan*/  cmd_type; } ;
struct nci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ST_NCI_CORE_PROP ; 
 int /*<<< orphan*/  ST_NCI_SET_NFC_MODE ; 
 int nci_prop_cmd (struct nci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_nci_init(struct nci_dev *ndev)
{
	struct nci_mode_set_cmd cmd;

	cmd.cmd_type = ST_NCI_SET_NFC_MODE;
	cmd.mode = 1;

	return nci_prop_cmd(ndev, ST_NCI_CORE_PROP,
			sizeof(struct nci_mode_set_cmd), (__u8 *)&cmd);
}