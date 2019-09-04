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
struct TYPE_2__ {struct ceph_crypto_key** data; } ;
struct key_preparsed_payload {TYPE_1__ payload; } ;
struct ceph_crypto_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_crypto_key_destroy (struct ceph_crypto_key*) ; 
 int /*<<< orphan*/  kfree (struct ceph_crypto_key*) ; 

__attribute__((used)) static void ceph_key_free_preparse(struct key_preparsed_payload *prep)
{
	struct ceph_crypto_key *ckey = prep->payload.data[0];
	ceph_crypto_key_destroy(ckey);
	kfree(ckey);
}