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
struct txx9aclc_plat_drvdata {scalar_t__ base; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACCTLDIS ; 
 int /*<<< orphan*/  ACCTL_ENLINK ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 struct txx9aclc_plat_drvdata* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/ * txx9aclc_drvdata ; 

__attribute__((used)) static int txx9aclc_ac97_remove(struct snd_soc_dai *dai)
{
	struct txx9aclc_plat_drvdata *drvdata = snd_soc_dai_get_drvdata(dai);

	/* disable AC-link */
	__raw_writel(ACCTL_ENLINK, drvdata->base + ACCTLDIS);
	txx9aclc_drvdata = NULL;
	return 0;
}