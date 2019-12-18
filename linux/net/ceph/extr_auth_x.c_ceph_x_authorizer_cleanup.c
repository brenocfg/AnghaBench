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
struct ceph_x_authorizer {int /*<<< orphan*/ * buf; int /*<<< orphan*/  session_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_buffer_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_crypto_key_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ceph_x_authorizer_cleanup(struct ceph_x_authorizer *au)
{
	ceph_crypto_key_destroy(&au->session_key);
	if (au->buf) {
		ceph_buffer_put(au->buf);
		au->buf = NULL;
	}
}