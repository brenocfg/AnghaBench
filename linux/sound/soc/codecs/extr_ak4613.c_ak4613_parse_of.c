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
struct device {struct device_node* of_node; } ;
struct ak4613_priv {int ic; int oc; } ;
typedef  int /*<<< orphan*/  prop ;

/* Variables and functions */
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void ak4613_parse_of(struct ak4613_priv *priv,
			    struct device *dev)
{
	struct device_node *np = dev->of_node;
	char prop[32];
	int i;

	/* Input 1 - 2 */
	for (i = 0; i < 2; i++) {
		snprintf(prop, sizeof(prop), "asahi-kasei,in%d-single-end", i + 1);
		if (!of_get_property(np, prop, NULL))
			priv->ic |= 1 << i;
	}

	/* Output 1 - 6 */
	for (i = 0; i < 6; i++) {
		snprintf(prop, sizeof(prop), "asahi-kasei,out%d-single-end", i + 1);
		if (!of_get_property(np, prop, NULL))
			priv->oc |= 1 << i;
	}
}