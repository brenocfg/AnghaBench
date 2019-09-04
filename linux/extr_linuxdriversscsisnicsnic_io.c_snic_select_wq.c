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
struct snic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int SNIC_WQ_MAX ; 

__attribute__((used)) static int
snic_select_wq(struct snic *snic)
{
	/* No multi queue support for now */
	BUILD_BUG_ON(SNIC_WQ_MAX > 1);

	return 0;
}