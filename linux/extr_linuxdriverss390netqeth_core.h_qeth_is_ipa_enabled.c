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
struct qeth_ipa_info {int supported_funcs; int enabled_funcs; } ;
typedef  enum qeth_ipa_funcs { ____Placeholder_qeth_ipa_funcs } qeth_ipa_funcs ;

/* Variables and functions */

__attribute__((used)) static inline int qeth_is_ipa_enabled(struct qeth_ipa_info *ipa,
		enum qeth_ipa_funcs func)
{
	return (ipa->supported_funcs & ipa->enabled_funcs & func);
}