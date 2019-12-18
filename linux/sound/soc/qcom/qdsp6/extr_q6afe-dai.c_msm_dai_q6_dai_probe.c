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
struct q6afe_port {int dummy; } ;
struct q6afe_dai_data {struct q6afe_port** port; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct q6afe_port*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct q6afe_dai_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct q6afe_port* q6afe_port_get_from_id (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int msm_dai_q6_dai_probe(struct snd_soc_dai *dai)
{
	struct q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	struct q6afe_port *port;

	port = q6afe_port_get_from_id(dai->dev, dai->id);
	if (IS_ERR(port)) {
		dev_err(dai->dev, "Unable to get afe port\n");
		return -EINVAL;
	}
	dai_data->port[dai->id] = port;

	return 0;
}