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
struct link_info {int link; int dais; int /*<<< orphan*/  conf; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct asoc_simple_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_count_dpcm ; 
 int /*<<< orphan*/  simple_count_noml ; 
 int /*<<< orphan*/  simple_for_each_link (struct asoc_simple_priv*,struct link_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* simple_priv_to_dev (struct asoc_simple_priv*) ; 

__attribute__((used)) static void simple_get_dais_count(struct asoc_simple_priv *priv,
				  struct link_info *li)
{
	struct device *dev = simple_priv_to_dev(priv);
	struct device_node *top = dev->of_node;

	/*
	 * link_num :	number of links.
	 *		CPU-Codec / CPU-dummy / dummy-Codec
	 * dais_num :	number of DAIs
	 * ccnf_num :	number of codec_conf
	 *		same number for "dummy-Codec"
	 *
	 * ex1)
	 * CPU0 --- Codec0	link : 5
	 * CPU1 --- Codec1	dais : 7
	 * CPU2 -/		ccnf : 1
	 * CPU3 --- Codec2
	 *
	 *	=> 5 links = 2xCPU-Codec + 2xCPU-dummy + 1xdummy-Codec
	 *	=> 7 DAIs  = 4xCPU + 3xCodec
	 *	=> 1 ccnf  = 1xdummy-Codec
	 *
	 * ex2)
	 * CPU0 --- Codec0	link : 5
	 * CPU1 --- Codec1	dais : 6
	 * CPU2 -/		ccnf : 1
	 * CPU3 -/
	 *
	 *	=> 5 links = 1xCPU-Codec + 3xCPU-dummy + 1xdummy-Codec
	 *	=> 6 DAIs  = 4xCPU + 2xCodec
	 *	=> 1 ccnf  = 1xdummy-Codec
	 *
	 * ex3)
	 * CPU0 --- Codec0	link : 6
	 * CPU1 -/		dais : 6
	 * CPU2 --- Codec1	ccnf : 2
	 * CPU3 -/
	 *
	 *	=> 6 links = 0xCPU-Codec + 4xCPU-dummy + 2xdummy-Codec
	 *	=> 6 DAIs  = 4xCPU + 2xCodec
	 *	=> 2 ccnf  = 2xdummy-Codec
	 *
	 * ex4)
	 * CPU0 --- Codec0 (convert-rate)	link : 3
	 * CPU1 --- Codec1			dais : 4
	 *					ccnf : 1
	 *
	 *	=> 3 links = 1xCPU-Codec + 1xCPU-dummy + 1xdummy-Codec
	 *	=> 4 DAIs  = 2xCPU + 2xCodec
	 *	=> 1 ccnf  = 1xdummy-Codec
	 */
	if (!top) {
		li->link = 1;
		li->dais = 2;
		li->conf = 0;
		return;
	}

	simple_for_each_link(priv, li,
			     simple_count_noml,
			     simple_count_dpcm);

	dev_dbg(dev, "link %d, dais %d, ccnf %d\n",
		li->link, li->dais, li->conf);
}