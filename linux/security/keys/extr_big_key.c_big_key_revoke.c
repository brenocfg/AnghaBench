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
struct path {int dummy; } ;
struct TYPE_2__ {scalar_t__* data; } ;
struct key {TYPE_1__ payload; } ;

/* Variables and functions */
 size_t BIG_KEY_FILE_THRESHOLD ; 
 size_t big_key_len ; 
 size_t big_key_path ; 
 scalar_t__ key_is_positive (struct key*) ; 
 int /*<<< orphan*/  key_payload_reserve (struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_truncate (struct path*,int /*<<< orphan*/ ) ; 

void big_key_revoke(struct key *key)
{
	struct path *path = (struct path *)&key->payload.data[big_key_path];

	/* clear the quota */
	key_payload_reserve(key, 0);
	if (key_is_positive(key) &&
	    (size_t)key->payload.data[big_key_len] > BIG_KEY_FILE_THRESHOLD)
		vfs_truncate(path, 0);
}