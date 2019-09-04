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
typedef  union key_payload {int dummy; } key_payload ;
struct key_type {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int EPERM ; 

int restrict_link_reject(struct key *keyring,
			 const struct key_type *type,
			 const union key_payload *payload,
			 struct key *restriction_key)
{
	return -EPERM;
}