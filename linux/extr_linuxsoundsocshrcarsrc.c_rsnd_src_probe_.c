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
struct rsnd_src {int irq; int /*<<< orphan*/  dma; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rsnd_mod*) ; 
 int rsnd_dma_attach (struct rsnd_dai_stream*,struct rsnd_mod*,int /*<<< orphan*/ *) ; 
 struct rsnd_src* rsnd_mod_to_src (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_src_interrupt ; 

__attribute__((used)) static int rsnd_src_probe_(struct rsnd_mod *mod,
			   struct rsnd_dai_stream *io,
			   struct rsnd_priv *priv)
{
	struct rsnd_src *src = rsnd_mod_to_src(mod);
	struct device *dev = rsnd_priv_to_dev(priv);
	int irq = src->irq;
	int ret;

	if (irq > 0) {
		/*
		 * IRQ is not supported on non-DT
		 * see
		 *	rsnd_src_irq()
		 */
		ret = devm_request_irq(dev, irq,
				       rsnd_src_interrupt,
				       IRQF_SHARED,
				       dev_name(dev), mod);
		if (ret)
			return ret;
	}

	ret = rsnd_dma_attach(io, mod, &src->dma);

	return ret;
}