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
struct se_dev_attrib {int pi_prot_verify; int /*<<< orphan*/  pi_prot_type; scalar_t__ hw_pi_prot_type; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 
 int strtobool (char const*,int*) ; 
 struct se_dev_attrib* to_attrib (struct config_item*) ; 

__attribute__((used)) static ssize_t pi_prot_verify_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	bool flag;
	int ret;

	ret = strtobool(page, &flag);
	if (ret < 0)
		return ret;

	if (!flag) {
		da->pi_prot_verify = flag;
		return count;
	}
	if (da->hw_pi_prot_type) {
		pr_warn("DIF protection enabled on underlying hardware,"
			" ignoring\n");
		return count;
	}
	if (!da->pi_prot_type) {
		pr_warn("DIF protection not supported by backend, ignoring\n");
		return count;
	}
	da->pi_prot_verify = flag;

	return count;
}