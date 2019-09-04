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
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static struct device_node *find_audio_device(const char *name)
{
	struct device_node *gpiop;
	struct device_node *np;
  
	gpiop = of_find_node_by_name(NULL, "gpio");
	if (! gpiop)
		return NULL;
  
	for (np = of_get_next_child(gpiop, NULL); np;
			np = of_get_next_child(gpiop, np)) {
		const char *property = of_get_property(np, "audio-gpio", NULL);
		if (property && strcmp(property, name) == 0)
			break;
	}  
	of_node_put(gpiop);
	return np;
}