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
struct ceph_options {struct ceph_options* mon_addr; struct ceph_options* key; struct ceph_options* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_crypto_key_destroy (struct ceph_options*) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_options*) ; 
 int /*<<< orphan*/  kfree (struct ceph_options*) ; 

void ceph_destroy_options(struct ceph_options *opt)
{
	dout("destroy_options %p\n", opt);
	kfree(opt->name);
	if (opt->key) {
		ceph_crypto_key_destroy(opt->key);
		kfree(opt->key);
	}
	kfree(opt->mon_addr);
	kfree(opt);
}