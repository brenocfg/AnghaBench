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
struct zcrypt_queue {int online; TYPE_2__* queue; struct zcrypt_card* zcard; } ;
struct zcrypt_card {int /*<<< orphan*/  online; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  qid; } ;
struct TYPE_3__ {struct zcrypt_queue* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ap_flush_queue (TYPE_2__*) ; 
 int sscanf (char const*,char*,int*) ; 
 TYPE_1__* to_ap_queue (struct device*) ; 

__attribute__((used)) static ssize_t online_store(struct device *dev,
			    struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct zcrypt_queue *zq = to_ap_queue(dev)->private;
	struct zcrypt_card *zc = zq->zcard;
	int online;

	if (sscanf(buf, "%d\n", &online) != 1 || online < 0 || online > 1)
		return -EINVAL;

	if (online && !zc->online)
		return -EINVAL;
	zq->online = online;

	ZCRYPT_DBF(DBF_INFO, "queue=%02x.%04x online=%d\n",
		   AP_QID_CARD(zq->queue->qid),
		   AP_QID_QUEUE(zq->queue->qid),
		   online);

	if (!online)
		ap_flush_queue(zq->queue);
	return count;
}