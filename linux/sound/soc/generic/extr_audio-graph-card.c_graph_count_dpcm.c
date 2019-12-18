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
struct link_info {int /*<<< orphan*/  dais; int /*<<< orphan*/  conf; int /*<<< orphan*/  link; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct asoc_simple_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct device* simple_priv_to_dev (struct asoc_simple_priv*) ; 

__attribute__((used)) static int graph_count_dpcm(struct asoc_simple_priv *priv,
			    struct device_node *cpu_ep,
			    struct device_node *codec_ep,
			    struct link_info *li,
			    int dup_codec)
{
	struct device *dev = simple_priv_to_dev(priv);

	li->link++; /* 1xCPU-dummy */
	li->dais++; /* 1xCPU */

	if (!dup_codec) {
		li->link++; /* 1xdummy-Codec */
		li->conf++; /* 1xdummy-Codec */
		li->dais++; /* 1xCodec */
	}

	dev_dbg(dev, "Count As DPCM\n");

	return 0;
}