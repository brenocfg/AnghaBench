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
struct key_type {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 struct key* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_IN_QUOTA ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* request_key_and_link (struct key_type*,char const*,void const*,size_t,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wait_for_key_construction (struct key*,int) ; 

struct key *request_key_with_auxdata(struct key_type *type,
				     const char *description,
				     const void *callout_info,
				     size_t callout_len,
				     void *aux)
{
	struct key *key;
	int ret;

	key = request_key_and_link(type, description, callout_info, callout_len,
				   aux, NULL, KEY_ALLOC_IN_QUOTA);
	if (!IS_ERR(key)) {
		ret = wait_for_key_construction(key, false);
		if (ret < 0) {
			key_put(key);
			return ERR_PTR(ret);
		}
	}
	return key;
}