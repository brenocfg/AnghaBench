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
typedef  int /*<<< orphan*/  u32 ;
struct aer_error {int pos_cap_err; int /*<<< orphan*/  source_id; int /*<<< orphan*/  root_status; int /*<<< orphan*/  header_log3; int /*<<< orphan*/  header_log2; int /*<<< orphan*/  header_log1; int /*<<< orphan*/  header_log0; int /*<<< orphan*/  cor_status; int /*<<< orphan*/  uncor_status; } ;

/* Variables and functions */
#define  PCI_ERR_COR_STATUS 132 
#define  PCI_ERR_HEADER_LOG 131 
#define  PCI_ERR_ROOT_ERR_SRC 130 
#define  PCI_ERR_ROOT_STATUS 129 
#define  PCI_ERR_UNCOR_STATUS 128 

__attribute__((used)) static u32 *find_pci_config_dword(struct aer_error *err, int where,
				  int *prw1cs)
{
	int rw1cs = 0;
	u32 *target = NULL;

	if (err->pos_cap_err == -1)
		return NULL;

	switch (where - err->pos_cap_err) {
	case PCI_ERR_UNCOR_STATUS:
		target = &err->uncor_status;
		rw1cs = 1;
		break;
	case PCI_ERR_COR_STATUS:
		target = &err->cor_status;
		rw1cs = 1;
		break;
	case PCI_ERR_HEADER_LOG:
		target = &err->header_log0;
		break;
	case PCI_ERR_HEADER_LOG+4:
		target = &err->header_log1;
		break;
	case PCI_ERR_HEADER_LOG+8:
		target = &err->header_log2;
		break;
	case PCI_ERR_HEADER_LOG+12:
		target = &err->header_log3;
		break;
	case PCI_ERR_ROOT_STATUS:
		target = &err->root_status;
		rw1cs = 1;
		break;
	case PCI_ERR_ROOT_ERR_SRC:
		target = &err->source_id;
		break;
	}
	if (prw1cs)
		*prw1cs = rw1cs;
	return target;
}