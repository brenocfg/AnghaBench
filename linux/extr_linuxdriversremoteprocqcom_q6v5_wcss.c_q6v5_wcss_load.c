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
struct rproc {int /*<<< orphan*/  firmware; struct q6v5_wcss* priv; } ;
struct q6v5_wcss {int /*<<< orphan*/  mem_reloc; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  mem_phys; int /*<<< orphan*/  mem_region; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int qcom_mdt_load_no_init (int /*<<< orphan*/ ,struct firmware const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int q6v5_wcss_load(struct rproc *rproc, const struct firmware *fw)
{
	struct q6v5_wcss *wcss = rproc->priv;

	return qcom_mdt_load_no_init(wcss->dev, fw, rproc->firmware,
				     0, wcss->mem_region, wcss->mem_phys,
				     wcss->mem_size, &wcss->mem_reloc);
}