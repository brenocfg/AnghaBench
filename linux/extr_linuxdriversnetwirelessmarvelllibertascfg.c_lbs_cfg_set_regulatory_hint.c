#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lbs_private {int regioncode; TYPE_1__* wdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct region_code_mapping const*) ; 
 int /*<<< orphan*/  regulatory_hint (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void lbs_cfg_set_regulatory_hint(struct lbs_private *priv)
{
	struct region_code_mapping {
		const char *cn;
		int code;
	};

	/* Section 5.17.2 */
	static const struct region_code_mapping regmap[] = {
		{"US ", 0x10}, /* US FCC */
		{"CA ", 0x20}, /* Canada */
		{"EU ", 0x30}, /* ETSI   */
		{"ES ", 0x31}, /* Spain  */
		{"FR ", 0x32}, /* France */
		{"JP ", 0x40}, /* Japan  */
	};
	size_t i;

	for (i = 0; i < ARRAY_SIZE(regmap); i++)
		if (regmap[i].code == priv->regioncode) {
			regulatory_hint(priv->wdev->wiphy, regmap[i].cn);
			break;
		}
}