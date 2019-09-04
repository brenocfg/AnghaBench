#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int buf_count; } ;
struct TYPE_4__ {TYPE_1__ in_buf_pool; } ;
struct qeth_card {scalar_t__ state; int /*<<< orphan*/  conf_mutex; TYPE_2__ qdio; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_RECOVER ; 
 int EINVAL ; 
 int EPERM ; 
 int QETH_IN_BUF_COUNT_MAX ; 
 int QETH_IN_BUF_COUNT_MIN ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qeth_realloc_buffer_pool (struct qeth_card*,int) ; 
 int simple_strtoul (char const*,char**,int) ; 

__attribute__((used)) static ssize_t qeth_dev_bufcnt_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	char *tmp;
	int cnt, old_cnt;
	int rc = 0;

	if (!card)
		return -EINVAL;

	mutex_lock(&card->conf_mutex);
	if ((card->state != CARD_STATE_DOWN) &&
	    (card->state != CARD_STATE_RECOVER)) {
		rc = -EPERM;
		goto out;
	}

	old_cnt = card->qdio.in_buf_pool.buf_count;
	cnt = simple_strtoul(buf, &tmp, 10);
	cnt = (cnt < QETH_IN_BUF_COUNT_MIN) ? QETH_IN_BUF_COUNT_MIN :
		((cnt > QETH_IN_BUF_COUNT_MAX) ? QETH_IN_BUF_COUNT_MAX : cnt);
	if (old_cnt != cnt) {
		rc = qeth_realloc_buffer_pool(card, cnt);
	}
out:
	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}