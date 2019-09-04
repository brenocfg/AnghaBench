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
struct qeth_card {scalar_t__ state; int /*<<< orphan*/  conf_mutex; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_RECOVER ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,char**,int) ; 

__attribute__((used)) static ssize_t qeth_dev_blkt_store(struct qeth_card *card,
		const char *buf, size_t count, int *value, int max_value)
{
	char *tmp;
	int i, rc = 0;

	if (!card)
		return -EINVAL;

	mutex_lock(&card->conf_mutex);
	if ((card->state != CARD_STATE_DOWN) &&
	    (card->state != CARD_STATE_RECOVER)) {
		rc = -EPERM;
		goto out;
	}
	i = simple_strtoul(buf, &tmp, 10);
	if (i <= max_value)
		*value = i;
	else
		rc = -EINVAL;
out:
	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}