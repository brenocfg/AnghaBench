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
struct key {int dummy; } ;
struct ecryptfs_auth_tok {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ecryptfs_auth_tok *
ecryptfs_get_encrypted_key_payload_data(struct key *key)
{
	return NULL;
}