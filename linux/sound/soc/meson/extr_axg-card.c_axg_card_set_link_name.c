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
struct snd_soc_dai_link {char* name; char* stream_name; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_card_set_link_name(struct snd_soc_card *card,
				  struct snd_soc_dai_link *link,
				  struct device_node *node,
				  const char *prefix)
{
	char *name = devm_kasprintf(card->dev, GFP_KERNEL, "%s.%s",
				    prefix, node->full_name);
	if (!name)
		return -ENOMEM;

	link->name = name;
	link->stream_name = name;

	return 0;
}