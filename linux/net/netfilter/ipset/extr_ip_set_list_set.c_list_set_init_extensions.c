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
struct set_elem {int dummy; } ;
struct ip_set_ext {int /*<<< orphan*/  timeout; } ;
struct ip_set {int dummy; } ;

/* Variables and functions */
 scalar_t__ SET_WITH_COMMENT (struct ip_set*) ; 
 scalar_t__ SET_WITH_COUNTER (struct ip_set*) ; 
 scalar_t__ SET_WITH_SKBINFO (struct ip_set*) ; 
 scalar_t__ SET_WITH_TIMEOUT (struct ip_set*) ; 
 int /*<<< orphan*/  ext_comment (struct set_elem*,struct ip_set*) ; 
 int /*<<< orphan*/  ext_counter (struct set_elem*,struct ip_set*) ; 
 int /*<<< orphan*/  ext_skbinfo (struct set_elem*,struct ip_set*) ; 
 int /*<<< orphan*/  ext_timeout (struct set_elem*,struct ip_set*) ; 
 int /*<<< orphan*/  ip_set_init_comment (struct ip_set*,int /*<<< orphan*/ ,struct ip_set_ext const*) ; 
 int /*<<< orphan*/  ip_set_init_counter (int /*<<< orphan*/ ,struct ip_set_ext const*) ; 
 int /*<<< orphan*/  ip_set_init_skbinfo (int /*<<< orphan*/ ,struct ip_set_ext const*) ; 
 int /*<<< orphan*/  ip_set_timeout_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
list_set_init_extensions(struct ip_set *set, const struct ip_set_ext *ext,
			 struct set_elem *e)
{
	if (SET_WITH_COUNTER(set))
		ip_set_init_counter(ext_counter(e, set), ext);
	if (SET_WITH_COMMENT(set))
		ip_set_init_comment(set, ext_comment(e, set), ext);
	if (SET_WITH_SKBINFO(set))
		ip_set_init_skbinfo(ext_skbinfo(e, set), ext);
	/* Update timeout last */
	if (SET_WITH_TIMEOUT(set))
		ip_set_timeout_set(ext_timeout(e, set), ext->timeout);
}