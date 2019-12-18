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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_2__ {scalar_t__ payload_len; scalar_t__ channel_len; scalar_t__ data; } ;
typedef  int Size ;
typedef  TYPE_1__ Notification ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_any (unsigned char const*,scalar_t__) ; 

__attribute__((used)) static uint32
notification_hash(const void *key, Size keysize)
{
	const Notification *k = *(const Notification *const *) key;

	Assert(keysize == sizeof(Notification *));
	/* We don't bother to include the payload's trailing null in the hash */
	return DatumGetUInt32(hash_any((const unsigned char *) k->data,
								   k->channel_len + k->payload_len + 1));
}