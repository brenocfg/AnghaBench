#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {int num_aux_devs; struct snd_soc_aux_dev* aux_dev; TYPE_1__* dev; } ;
struct snd_soc_aux_dev {int /*<<< orphan*/  codec_of_node; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct snd_soc_aux_dev* devm_kcalloc (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int of_count_phandle_with_args (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_parse_phandle (struct device_node*,char*,int) ; 

__attribute__((used)) static int axg_card_add_aux_devices(struct snd_soc_card *card)
{
	struct device_node *node = card->dev->of_node;
	struct snd_soc_aux_dev *aux;
	int num, i;

	num = of_count_phandle_with_args(node, "audio-aux-devs", NULL);
	if (num == -ENOENT) {
		/*
		 * It is ok to have no auxiliary devices but for this card it
		 * is a strange situtation. Let's warn the about it.
		 */
		dev_warn(card->dev, "card has no auxiliary devices\n");
		return 0;
	} else if (num < 0) {
		dev_err(card->dev, "error getting auxiliary devices: %d\n",
			num);
		return num;
	}

	aux = devm_kcalloc(card->dev, num, sizeof(*aux), GFP_KERNEL);
	if (!aux)
		return -ENOMEM;
	card->aux_dev = aux;
	card->num_aux_devs = num;

	for (i = 0; i < card->num_aux_devs; i++, aux++) {
		aux->codec_of_node =
			of_parse_phandle(node, "audio-aux-devs", i);
		if (!aux->codec_of_node)
			return -EINVAL;
	}

	return 0;
}