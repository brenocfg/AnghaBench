#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ima_field_data {int dummy; } ;
struct ima_event_data {TYPE_2__* iint; scalar_t__ violation; } ;
struct TYPE_4__ {TYPE_1__* ima_hash; } ;
struct TYPE_3__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  length; int /*<<< orphan*/ * digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ALGO_SHA1 ; 
 int ima_eventdigest_init_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ima_field_data*) ; 

int ima_eventdigest_ng_init(struct ima_event_data *event_data,
			    struct ima_field_data *field_data)
{
	u8 *cur_digest = NULL, hash_algo = HASH_ALGO_SHA1;
	u32 cur_digestsize = 0;

	if (event_data->violation)	/* recording a violation. */
		goto out;

	cur_digest = event_data->iint->ima_hash->digest;
	cur_digestsize = event_data->iint->ima_hash->length;

	hash_algo = event_data->iint->ima_hash->algo;
out:
	return ima_eventdigest_init_common(cur_digest, cur_digestsize,
					   hash_algo, field_data);
}