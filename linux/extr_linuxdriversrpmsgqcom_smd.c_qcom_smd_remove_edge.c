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
struct qcom_smd_edge {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int qcom_smd_unregister_edge (struct qcom_smd_edge*) ; 
 struct qcom_smd_edge* to_smd_edge (struct device*) ; 

__attribute__((used)) static int qcom_smd_remove_edge(struct device *dev, void *data)
{
	struct qcom_smd_edge *edge = to_smd_edge(dev);

	return qcom_smd_unregister_edge(edge);
}