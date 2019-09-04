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
struct snd_card {char const* components; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

int snd_component_add(struct snd_card *card, const char *component)
{
	char *ptr;
	int len = strlen(component);

	ptr = strstr(card->components, component);
	if (ptr != NULL) {
		if (ptr[len] == '\0' || ptr[len] == ' ')	/* already there */
			return 1;
	}
	if (strlen(card->components) + 1 + len + 1 > sizeof(card->components)) {
		snd_BUG();
		return -ENOMEM;
	}
	if (card->components[0] != '\0')
		strcat(card->components, " ");
	strcat(card->components, component);
	return 0;
}