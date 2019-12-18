#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int axg_card_parse_of_optional(struct snd_soc_card *card,
				      const char *propname,
				      int (*func)(struct snd_soc_card *c,
						  const char *p))
{
	/* If property is not provided, don't fail ... */
	if (!of_property_read_bool(card->dev->of_node, propname))
		return 0;

	/* ... but do fail if it is provided and the parsing fails */
	return func(card, propname);
}