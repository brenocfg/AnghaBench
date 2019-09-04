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
struct rproc {int dummy; } ;
struct qcom_sysmon {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct qcom_sysmon *qcom_add_sysmon_subdev(struct rproc *rproc,
							 const char *name,
							 int ssctl_instance)
{
	return NULL;
}