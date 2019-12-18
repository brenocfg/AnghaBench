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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ima_field_data {int dummy; } ;
struct ima_event_data {int /*<<< orphan*/  modsig; scalar_t__ violation; } ;
typedef  enum hash_algo { ____Placeholder_hash_algo } hash_algo ;

/* Variables and functions */
 int EINVAL ; 
 int HASH_ALGO_SHA1 ; 
 int HASH_ALGO__LAST ; 
 int ima_eventdigest_init_common (int /*<<< orphan*/  const*,scalar_t__,int,struct ima_field_data*) ; 
 int ima_get_modsig_digest (int /*<<< orphan*/ ,int*,int /*<<< orphan*/  const**,scalar_t__*) ; 

int ima_eventdigest_modsig_init(struct ima_event_data *event_data,
				struct ima_field_data *field_data)
{
	enum hash_algo hash_algo;
	const u8 *cur_digest;
	u32 cur_digestsize;

	if (!event_data->modsig)
		return 0;

	if (event_data->violation) {
		/* Recording a violation. */
		hash_algo = HASH_ALGO_SHA1;
		cur_digest = NULL;
		cur_digestsize = 0;
	} else {
		int rc;

		rc = ima_get_modsig_digest(event_data->modsig, &hash_algo,
					   &cur_digest, &cur_digestsize);
		if (rc)
			return rc;
		else if (hash_algo == HASH_ALGO__LAST || cur_digestsize == 0)
			/* There was some error collecting the digest. */
			return -EINVAL;
	}

	return ima_eventdigest_init_common(cur_digest, cur_digestsize,
					   hash_algo, field_data);
}