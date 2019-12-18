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
typedef  int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 void* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static struct device_node *get_gpio(char *name,
				    char *altname,
				    int *gpioptr,
				    int *gpioactiveptr)
{
	struct device_node *np, *gpio;
	const u32 *reg;
	const char *audio_gpio;

	*gpioptr = -1;

	/* check if we can get it the easy way ... */
	np = of_find_node_by_name(NULL, name);
	if (!np) {
		/* some machines have only gpioX/extint-gpioX nodes,
		 * and an audio-gpio property saying what it is ...
		 * So what we have to do is enumerate all children
		 * of the gpio node and check them all. */
		gpio = of_find_node_by_name(NULL, "gpio");
		if (!gpio)
			return NULL;
		while ((np = of_get_next_child(gpio, np))) {
			audio_gpio = of_get_property(np, "audio-gpio", NULL);
			if (!audio_gpio)
				continue;
			if (strcmp(audio_gpio, name) == 0)
				break;
			if (altname && (strcmp(audio_gpio, altname) == 0))
				break;
		}
		of_node_put(gpio);
		/* still not found, assume not there */
		if (!np)
			return NULL;
	}

	reg = of_get_property(np, "reg", NULL);
	if (!reg) {
		of_node_put(np);
		return NULL;
	}

	*gpioptr = *reg;

	/* this is a hack, usually the GPIOs 'reg' property
	 * should have the offset based from the GPIO space
	 * which is at 0x50, but apparently not always... */
	if (*gpioptr < 0x50)
		*gpioptr += 0x50;

	reg = of_get_property(np, "audio-gpio-active-state", NULL);
	if (!reg)
		/* Apple seems to default to 1, but
		 * that doesn't seem right at least on most
		 * machines. So until proven that the opposite
		 * is necessary, we default to 0
		 * (which, incidentally, snd-powermac also does...) */
		*gpioactiveptr = 0;
	else
		*gpioactiveptr = *reg;

	return np;
}