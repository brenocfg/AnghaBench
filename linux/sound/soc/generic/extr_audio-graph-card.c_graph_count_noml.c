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
struct link_info {int link; int dais; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct asoc_simple_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct device* simple_priv_to_dev (struct asoc_simple_priv*) ; 

__attribute__((used)) static int graph_count_noml(struct asoc_simple_priv *priv,
			    struct device_node *cpu_ep,
			    struct device_node *codec_ep,
			    struct link_info *li)
{
	struct device *dev = simple_priv_to_dev(priv);

	li->link += 1; /* 1xCPU-Codec */
	li->dais += 2; /* 1xCPU + 1xCodec */

	dev_dbg(dev, "Count As Normal\n");

	return 0;
}