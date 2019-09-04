#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  re; } ;
typedef  TYPE_1__ zend_regexp_list ;
typedef  int zend_bool ;
struct TYPE_5__ {TYPE_1__* regexp_list; } ;
typedef  TYPE_2__ zend_blacklist ;
typedef  int /*<<< orphan*/  pcre2_match_data ;
typedef  int /*<<< orphan*/  pcre2_match_context ;
typedef  int /*<<< orphan*/  PCRE2_SPTR ;

/* Variables and functions */
 int pcre2_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_pcre_create_match_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pcre_free_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_pcre_mctx () ; 

zend_bool zend_accel_blacklist_is_blacklisted(zend_blacklist *blacklist, char *verify_path, size_t verify_path_len)
{
	int ret = 0;
	zend_regexp_list *regexp_list_it = blacklist->regexp_list;
	pcre2_match_context *mctx = php_pcre_mctx();

	if (regexp_list_it == NULL) {
		return 0;
	}
	while (regexp_list_it != NULL) {
		pcre2_match_data *match_data = php_pcre_create_match_data(0, regexp_list_it->re);
		if (!match_data) {
			/* Alloc failed, but next one could still come through and match. */
			continue;
		}
		int rc = pcre2_match(regexp_list_it->re, (PCRE2_SPTR)verify_path, verify_path_len, 0, 0, match_data, mctx);
		if (rc >= 0) {
			ret = 1;
			php_pcre_free_match_data(match_data);
			break;
		}
		php_pcre_free_match_data(match_data);
		regexp_list_it = regexp_list_it->next;
	}
	return ret;
}