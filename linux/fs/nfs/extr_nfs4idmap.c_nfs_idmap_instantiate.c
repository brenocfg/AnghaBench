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
struct key {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  thread_keyring; } ;

/* Variables and functions */
 TYPE_1__* id_resolver_cache ; 
 int key_instantiate_and_link (struct key*,char*,size_t,int /*<<< orphan*/ ,struct key*) ; 

__attribute__((used)) static int nfs_idmap_instantiate(struct key *key, struct key *authkey, char *data, size_t datalen)
{
	return key_instantiate_and_link(key, data, datalen,
					id_resolver_cache->thread_keyring,
					authkey);
}