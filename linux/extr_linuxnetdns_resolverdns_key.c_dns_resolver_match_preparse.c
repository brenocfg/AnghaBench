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
struct key_match_data {int /*<<< orphan*/  cmp; int /*<<< orphan*/  lookup_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYRING_SEARCH_LOOKUP_ITERATE ; 
 int /*<<< orphan*/  dns_resolver_cmp ; 

__attribute__((used)) static int dns_resolver_match_preparse(struct key_match_data *match_data)
{
	match_data->lookup_type = KEYRING_SEARCH_LOOKUP_ITERATE;
	match_data->cmp = dns_resolver_cmp;
	return 0;
}