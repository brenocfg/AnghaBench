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
struct snd_ice1712 {int /*<<< orphan*/  card; } ;
struct TYPE_2__ {int /*<<< orphan*/ * write; int /*<<< orphan*/ * unlock; int /*<<< orphan*/ * lock; } ;
struct snd_akm4xxx {unsigned long* private_value; TYPE_1__ ops; struct snd_ice1712** private_data; int /*<<< orphan*/  card; } ;
struct snd_ak4xxx_private {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_ak4xxx_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_akm4xxx_init (struct snd_akm4xxx*) ; 
 int /*<<< orphan*/ * snd_ice1712_akm4xxx_lock ; 
 int /*<<< orphan*/ * snd_ice1712_akm4xxx_unlock ; 
 int /*<<< orphan*/ * snd_ice1712_akm4xxx_write ; 

int snd_ice1712_akm4xxx_init(struct snd_akm4xxx *ak, const struct snd_akm4xxx *temp,
			     const struct snd_ak4xxx_private *_priv, struct snd_ice1712 *ice)
{
	struct snd_ak4xxx_private *priv;

	if (_priv != NULL) {
		priv = kmalloc(sizeof(*priv), GFP_KERNEL);
		if (priv == NULL)
			return -ENOMEM;
		*priv = *_priv;
	} else {
		priv = NULL;
	}
	*ak = *temp;
	ak->card = ice->card;
        ak->private_value[0] = (unsigned long)priv;
	ak->private_data[0] = ice;
	if (ak->ops.lock == NULL)
		ak->ops.lock = snd_ice1712_akm4xxx_lock;
	if (ak->ops.unlock == NULL)
		ak->ops.unlock = snd_ice1712_akm4xxx_unlock;
	if (ak->ops.write == NULL)
		ak->ops.write = snd_ice1712_akm4xxx_write;
	snd_akm4xxx_init(ak);
	return 0;
}