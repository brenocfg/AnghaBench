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
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_REPORT_PHYS ; 
 int pqi_report_phys_logical_luns (struct pqi_ctrl_info*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static inline int pqi_report_phys_luns(struct pqi_ctrl_info *ctrl_info,
	void **buffer)
{
	return pqi_report_phys_logical_luns(ctrl_info, CISS_REPORT_PHYS,
		buffer);
}