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
struct path {int /*<<< orphan*/ * dentry; int /*<<< orphan*/ * mnt; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** data; } ;
struct key {TYPE_1__ payload; } ;

/* Variables and functions */
 size_t BIG_KEY_FILE_THRESHOLD ; 
 size_t big_key_data ; 
 size_t big_key_len ; 
 size_t big_key_path ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 

void big_key_destroy(struct key *key)
{
	size_t datalen = (size_t)key->payload.data[big_key_len];

	if (datalen > BIG_KEY_FILE_THRESHOLD) {
		struct path *path = (struct path *)&key->payload.data[big_key_path];

		path_put(path);
		path->mnt = NULL;
		path->dentry = NULL;
	}
	kzfree(key->payload.data[big_key_data]);
	key->payload.data[big_key_data] = NULL;
}