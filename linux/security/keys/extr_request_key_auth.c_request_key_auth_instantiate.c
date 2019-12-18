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
struct request_key_auth {int dummy; } ;
struct key_preparsed_payload {scalar_t__ data; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_assign_keypointer (struct key*,struct request_key_auth*) ; 

__attribute__((used)) static int request_key_auth_instantiate(struct key *key,
					struct key_preparsed_payload *prep)
{
	rcu_assign_keypointer(key, (struct request_key_auth *)prep->data);
	return 0;
}