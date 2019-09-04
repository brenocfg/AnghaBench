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
struct ti_qspi {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ti_qspi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ti_qspi_restore_ctx (struct ti_qspi*) ; 

__attribute__((used)) static int ti_qspi_runtime_resume(struct device *dev)
{
	struct ti_qspi      *qspi;

	qspi = dev_get_drvdata(dev);
	ti_qspi_restore_ctx(qspi);

	return 0;
}