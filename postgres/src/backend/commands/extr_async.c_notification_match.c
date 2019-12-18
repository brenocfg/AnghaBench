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
struct TYPE_2__ {scalar_t__ channel_len; scalar_t__ payload_len; int /*<<< orphan*/  data; } ;
typedef  int Size ;
typedef  TYPE_1__ Notification ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
notification_match(const void *key1, const void *key2, Size keysize)
{
	const Notification *k1 = *(const Notification *const *) key1;
	const Notification *k2 = *(const Notification *const *) key2;

	Assert(keysize == sizeof(Notification *));
	if (k1->channel_len == k2->channel_len &&
		k1->payload_len == k2->payload_len &&
		memcmp(k1->data, k2->data,
			   k1->channel_len + k1->payload_len + 2) == 0)
		return 0;				/* equal */
	return 1;					/* not equal */
}