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
struct rt274_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT274_GET_HP_SENSE ; 
 int /*<<< orphan*/  RT274_GET_MIC_SENSE ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int rt274_jack_detect(struct rt274_priv *rt274, bool *hp, bool *mic)
{
	unsigned int buf;
	int ret;

	*hp = false;
	*mic = false;

	if (!rt274->component)
		return -EINVAL;

	ret = regmap_read(rt274->regmap, RT274_GET_HP_SENSE, &buf);
	if (ret)
		return ret;

	*hp = buf & 0x80000000;
	ret = regmap_read(rt274->regmap, RT274_GET_MIC_SENSE, &buf);
	if (ret)
		return ret;

	*mic = buf & 0x80000000;

	pr_debug("*hp = %d *mic = %d\n", *hp, *mic);

	return 0;
}