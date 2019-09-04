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
struct net_device {int flags; int mtu; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ctcm_priv {unsigned int buffer_size; TYPE_1__** channel; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {unsigned int max_bufsize; int /*<<< orphan*/  flags; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_FLAGS_BUFSIZE_CHANGED ; 
 unsigned int CTCM_BUFSIZE_LIMIT ; 
 int /*<<< orphan*/  CTCM_DBF_DEV (int /*<<< orphan*/ ,struct net_device*,char const*) ; 
 int /*<<< orphan*/  CTCM_DBF_TEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t CTCM_READ ; 
 size_t CTCM_WRITE ; 
 int /*<<< orphan*/  CTC_DBF_ERROR ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 int IFF_RUNNING ; 
 int LL_HEADER_LENGTH ; 
 int /*<<< orphan*/  SETUP ; 
 struct ctcm_priv* dev_get_drvdata (struct device*) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static ssize_t ctcm_buffer_write(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct net_device *ndev;
	unsigned int bs1;
	struct ctcm_priv *priv = dev_get_drvdata(dev);
	int rc;

	ndev = priv->channel[CTCM_READ]->netdev;
	if (!(priv && priv->channel[CTCM_READ] && ndev)) {
		CTCM_DBF_TEXT(SETUP, CTC_DBF_ERROR, "bfnondev");
		return -ENODEV;
	}

	rc = kstrtouint(buf, 0, &bs1);
	if (rc)
		goto einval;
	if (bs1 > CTCM_BUFSIZE_LIMIT)
					goto einval;
	if (bs1 < (576 + LL_HEADER_LENGTH + 2))
					goto einval;
	priv->buffer_size = bs1;	/* just to overwrite the default */

	if ((ndev->flags & IFF_RUNNING) &&
	    (bs1 < (ndev->mtu + LL_HEADER_LENGTH + 2)))
					goto einval;

	priv->channel[CTCM_READ]->max_bufsize = bs1;
	priv->channel[CTCM_WRITE]->max_bufsize = bs1;
	if (!(ndev->flags & IFF_RUNNING))
		ndev->mtu = bs1 - LL_HEADER_LENGTH - 2;
	priv->channel[CTCM_READ]->flags |= CHANNEL_FLAGS_BUFSIZE_CHANGED;
	priv->channel[CTCM_WRITE]->flags |= CHANNEL_FLAGS_BUFSIZE_CHANGED;

	CTCM_DBF_DEV(SETUP, ndev, buf);
	return count;

einval:
	CTCM_DBF_DEV(SETUP, ndev, "buff_err");
	return -EINVAL;
}