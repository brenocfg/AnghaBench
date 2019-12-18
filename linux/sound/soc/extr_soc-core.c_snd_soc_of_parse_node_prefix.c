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
struct snd_soc_codec_conf {char const* name_prefix; struct device_node* of_node; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_read_string (struct device_node*,char const*,char const**) ; 

void snd_soc_of_parse_node_prefix(struct device_node *np,
				  struct snd_soc_codec_conf *codec_conf,
				  struct device_node *of_node,
				  const char *propname)
{
	const char *str;
	int ret;

	ret = of_property_read_string(np, propname, &str);
	if (ret < 0) {
		/* no prefix is not error */
		return;
	}

	codec_conf->of_node	= of_node;
	codec_conf->name_prefix	= str;
}