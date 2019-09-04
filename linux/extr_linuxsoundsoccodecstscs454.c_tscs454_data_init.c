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
struct tscs454 {int /*<<< orphan*/  sub_ram; int /*<<< orphan*/  spk_ram; int /*<<< orphan*/  dac_ram; int /*<<< orphan*/  pll2; int /*<<< orphan*/  pll1; int /*<<< orphan*/  aifs_status_lock; int /*<<< orphan*/ * aifs; int /*<<< orphan*/  regmap; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int TSCS454_DAI_COUNT ; 
 int /*<<< orphan*/  aif_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  coeff_ram_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pll_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tscs454_regmap_cfg ; 

__attribute__((used)) static inline int tscs454_data_init(struct tscs454 *tscs454,
		struct i2c_client *i2c)
{
	int i;
	int ret;

	tscs454->regmap = devm_regmap_init_i2c(i2c, &tscs454_regmap_cfg);
	if (IS_ERR(tscs454->regmap)) {
		ret = PTR_ERR(tscs454->regmap);
		return ret;
	}

	for (i = 0; i < TSCS454_DAI_COUNT; i++)
		aif_init(&tscs454->aifs[i], i);

	mutex_init(&tscs454->aifs_status_lock);
	pll_init(&tscs454->pll1, 1);
	pll_init(&tscs454->pll2, 2);

	coeff_ram_init(&tscs454->dac_ram);
	coeff_ram_init(&tscs454->spk_ram);
	coeff_ram_init(&tscs454->sub_ram);

	return 0;
}