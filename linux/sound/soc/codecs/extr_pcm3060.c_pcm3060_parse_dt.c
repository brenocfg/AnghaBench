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
struct pcm3060_priv {int /*<<< orphan*/  out_se; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_property_read_bool (struct device_node const*,char*) ; 

__attribute__((used)) static void pcm3060_parse_dt(const struct device_node *np,
			     struct pcm3060_priv *priv)
{
	priv->out_se = of_property_read_bool(np, "ti,out-single-ended");
}