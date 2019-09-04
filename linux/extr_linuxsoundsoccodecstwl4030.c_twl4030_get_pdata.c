#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct twl4030_codec_data {int dummy; } ;
struct snd_soc_component {TYPE_2__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {TYPE_1__* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct twl4030_codec_data* dev_get_platdata (TYPE_2__*) ; 
 struct twl4030_codec_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  twl4030_setup_pdata_of (struct twl4030_codec_data*,struct device_node*) ; 

__attribute__((used)) static struct twl4030_codec_data *twl4030_get_pdata(struct snd_soc_component *component)
{
	struct twl4030_codec_data *pdata = dev_get_platdata(component->dev);
	struct device_node *twl4030_codec_node = NULL;

	twl4030_codec_node = of_get_child_by_name(component->dev->parent->of_node,
						  "codec");

	if (!pdata && twl4030_codec_node) {
		pdata = devm_kzalloc(component->dev,
				     sizeof(struct twl4030_codec_data),
				     GFP_KERNEL);
		if (!pdata) {
			of_node_put(twl4030_codec_node);
			return NULL;
		}
		twl4030_setup_pdata_of(pdata, twl4030_codec_node);
		of_node_put(twl4030_codec_node);
	}

	return pdata;
}