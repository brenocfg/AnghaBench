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
struct se_cmd {int prot_op; } ;

/* Variables and functions */
#define  TARGET_PROT_DIN_INSERT 133 
#define  TARGET_PROT_DIN_PASS 132 
#define  TARGET_PROT_DIN_STRIP 131 
#define  TARGET_PROT_DOUT_INSERT 130 
#define  TARGET_PROT_DOUT_PASS 129 
#define  TARGET_PROT_DOUT_STRIP 128 

__attribute__((used)) static inline int
qla_tgt_ref_mask_check(struct se_cmd *se_cmd)
{
	switch (se_cmd->prot_op) {
	case TARGET_PROT_DIN_INSERT:
	case TARGET_PROT_DOUT_INSERT:
	case TARGET_PROT_DIN_STRIP:
	case TARGET_PROT_DOUT_STRIP:
	case TARGET_PROT_DIN_PASS:
	case TARGET_PROT_DOUT_PASS:
	    return 1;
	default:
	    return 0;
	}
	return 0;
}