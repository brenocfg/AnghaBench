#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/  re; } ;
typedef  TYPE_1__ pcre_cache_entry ;

/* Variables and functions */
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  pcre2_code_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_efree_pcre_cache(zval *data) /* {{{ */
{
	pcre_cache_entry *pce = (pcre_cache_entry *) Z_PTR_P(data);
	if (!pce) return;
	pcre2_code_free(pce->re);
	efree(pce);
}