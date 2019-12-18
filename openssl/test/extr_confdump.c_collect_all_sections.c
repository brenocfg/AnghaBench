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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ CONF ;

/* Variables and functions */
 int /*<<< orphan*/  collect_section_name ; 
 int /*<<< orphan*/  lh_CONF_VALUE_doall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  section_name_cmp ; 
 int /*<<< orphan*/  section_names ; 
 int /*<<< orphan*/  sk_OPENSSL_CSTRING_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_OPENSSL_CSTRING_sort (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void collect_all_sections(const CONF *cnf)
{
    section_names = sk_OPENSSL_CSTRING_new(section_name_cmp);
    lh_CONF_VALUE_doall(cnf->data, collect_section_name);
    sk_OPENSSL_CSTRING_sort(section_names);
}