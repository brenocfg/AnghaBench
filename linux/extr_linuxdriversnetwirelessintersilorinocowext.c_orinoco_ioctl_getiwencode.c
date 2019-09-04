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
struct orinoco_private {int tx_key; TYPE_1__* keys; scalar_t__ wep_restrict; int /*<<< orphan*/  encode_alg; int /*<<< orphan*/  has_wep; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int /*<<< orphan*/  length; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 int ORINOCO_MAX_KEYS ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_getiwencode(struct net_device *dev,
				     struct iw_request_info *info,
				     struct iw_point *erq,
				     char *keybuf)
{
	struct orinoco_private *priv = ndev_priv(dev);
	int index = (erq->flags & IW_ENCODE_INDEX) - 1;
	unsigned long flags;

	if (!priv->has_wep)
		return -EOPNOTSUPP;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	if ((index < 0) || (index >= ORINOCO_MAX_KEYS))
		index = priv->tx_key;

	erq->flags = 0;
	if (!priv->encode_alg)
		erq->flags |= IW_ENCODE_DISABLED;
	erq->flags |= index + 1;

	if (priv->wep_restrict)
		erq->flags |= IW_ENCODE_RESTRICTED;
	else
		erq->flags |= IW_ENCODE_OPEN;

	erq->length = priv->keys[index].key_len;

	memcpy(keybuf, priv->keys[index].key, erq->length);

	orinoco_unlock(priv, &flags);
	return 0;
}