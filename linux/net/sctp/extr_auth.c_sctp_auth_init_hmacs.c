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
struct sctp_endpoint {struct crypto_shash** auth_hmacs; } ;
struct crypto_shash {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  size_t __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  hmac_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 size_t SCTP_AUTH_NUM_HMACS ; 
 struct crypto_shash* crypto_alloc_shash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_shash** kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_destroy_hmacs (struct crypto_shash**) ; 
 TYPE_1__* sctp_hmac_list ; 

int sctp_auth_init_hmacs(struct sctp_endpoint *ep, gfp_t gfp)
{
	struct crypto_shash *tfm = NULL;
	__u16   id;

	/* If the transforms are already allocated, we are done */
	if (ep->auth_hmacs)
		return 0;

	/* Allocated the array of pointers to transorms */
	ep->auth_hmacs = kcalloc(SCTP_AUTH_NUM_HMACS,
				 sizeof(struct crypto_shash *),
				 gfp);
	if (!ep->auth_hmacs)
		return -ENOMEM;

	for (id = 0; id < SCTP_AUTH_NUM_HMACS; id++) {

		/* See is we support the id.  Supported IDs have name and
		 * length fields set, so that we can allocated and use
		 * them.  We can safely just check for name, for without the
		 * name, we can't allocate the TFM.
		 */
		if (!sctp_hmac_list[id].hmac_name)
			continue;

		/* If this TFM has been allocated, we are all set */
		if (ep->auth_hmacs[id])
			continue;

		/* Allocate the ID */
		tfm = crypto_alloc_shash(sctp_hmac_list[id].hmac_name, 0, 0);
		if (IS_ERR(tfm))
			goto out_err;

		ep->auth_hmacs[id] = tfm;
	}

	return 0;

out_err:
	/* Clean up any successful allocations */
	sctp_auth_destroy_hmacs(ep->auth_hmacs);
	return -ENOMEM;
}