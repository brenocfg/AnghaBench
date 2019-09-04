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
struct trusted_key_payload {int migratable; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int key_payload_reserve (struct key*,int) ; 
 struct trusted_key_payload* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct trusted_key_payload *trusted_payload_alloc(struct key *key)
{
	struct trusted_key_payload *p = NULL;
	int ret;

	ret = key_payload_reserve(key, sizeof *p);
	if (ret < 0)
		return p;
	p = kzalloc(sizeof *p, GFP_KERNEL);
	if (p)
		p->migratable = 1; /* migratable by default */
	return p;
}