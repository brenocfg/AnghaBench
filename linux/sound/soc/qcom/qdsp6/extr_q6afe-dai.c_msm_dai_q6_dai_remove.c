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
struct snd_soc_dai {size_t id; int /*<<< orphan*/  dev; } ;
struct q6afe_dai_data {int /*<<< orphan*/ ** port; } ;

/* Variables and functions */
 struct q6afe_dai_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6afe_port_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_dai_q6_dai_remove(struct snd_soc_dai *dai)
{
	struct q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);

	q6afe_port_put(dai_data->port[dai->id]);
	dai_data->port[dai->id] = NULL;

	return 0;
}