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
struct lcs_card {int /*<<< orphan*/  portno; TYPE_1__* dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev_port; } ;

/* Variables and functions */
 size_t EINVAL ; 
 struct lcs_card* dev_get_drvdata (struct device*) ; 
 int kstrtos16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
lcs_portno_store (struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
        struct lcs_card *card;
	int rc;
	s16 value;

	card = dev_get_drvdata(dev);

        if (!card)
                return 0;

	rc = kstrtos16(buf, 0, &value);
	if (rc)
		return -EINVAL;
        /* TODO: sanity checks */
        card->portno = value;
	if (card->dev)
		card->dev->dev_port = card->portno;

        return count;

}