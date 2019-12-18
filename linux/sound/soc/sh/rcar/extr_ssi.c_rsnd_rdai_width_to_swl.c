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
typedef  int /*<<< orphan*/  u32 ;
struct rsnd_priv {int dummy; } ;
struct rsnd_dai {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWL_16 ; 
 int /*<<< orphan*/  SWL_24 ; 
 int /*<<< orphan*/  SWL_32 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 struct rsnd_priv* rsnd_rdai_to_priv (struct rsnd_dai*) ; 
 int rsnd_rdai_width_get (struct rsnd_dai*) ; 

__attribute__((used)) static u32 rsnd_rdai_width_to_swl(struct rsnd_dai *rdai)
{
	struct rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	struct device *dev = rsnd_priv_to_dev(priv);
	int width = rsnd_rdai_width_get(rdai);

	switch (width) {
	case 32: return SWL_32;
	case 24: return SWL_24;
	case 16: return SWL_16;
	}

	dev_err(dev, "unsupported slot width value: %d\n", width);
	return 0;
}