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
struct brcmf_chip {int dummy; } ;
struct brcmf_chip_priv {struct brcmf_chip pub; void* ctx; struct brcmf_buscore_ops const* ops; scalar_t__ num_cores; int /*<<< orphan*/  cores; } ;
struct brcmf_buscore_ops {int (* prepare ) (void*) ;int /*<<< orphan*/  activate; int /*<<< orphan*/  write32; int /*<<< orphan*/  read32; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct brcmf_chip* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  brcmf_chip_detach (struct brcmf_chip*) ; 
 int brcmf_chip_recognition (struct brcmf_chip_priv*) ; 
 int brcmf_chip_setup (struct brcmf_chip_priv*) ; 
 struct brcmf_chip_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (void*) ; 

struct brcmf_chip *brcmf_chip_attach(void *ctx,
				     const struct brcmf_buscore_ops *ops)
{
	struct brcmf_chip_priv *chip;
	int err = 0;

	if (WARN_ON(!ops->read32))
		err = -EINVAL;
	if (WARN_ON(!ops->write32))
		err = -EINVAL;
	if (WARN_ON(!ops->prepare))
		err = -EINVAL;
	if (WARN_ON(!ops->activate))
		err = -EINVAL;
	if (err < 0)
		return ERR_PTR(-EINVAL);

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&chip->cores);
	chip->num_cores = 0;
	chip->ops = ops;
	chip->ctx = ctx;

	err = ops->prepare(ctx);
	if (err < 0)
		goto fail;

	err = brcmf_chip_recognition(chip);
	if (err < 0)
		goto fail;

	err = brcmf_chip_setup(chip);
	if (err < 0)
		goto fail;

	return &chip->pub;

fail:
	brcmf_chip_detach(&chip->pub);
	return ERR_PTR(err);
}