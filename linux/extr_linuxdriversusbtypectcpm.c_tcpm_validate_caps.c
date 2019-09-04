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
typedef  int /*<<< orphan*/  u32 ;
struct tcpm_port {int dummy; } ;
typedef  enum pdo_err { ____Placeholder_pdo_err } pdo_err ;

/* Variables and functions */
 int EINVAL ; 
 int PDO_NO_ERR ; 
 int /*<<< orphan*/ * pdo_err_msg ; 
 int tcpm_caps_err (struct tcpm_port*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  tcpm_log_force (struct tcpm_port*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpm_validate_caps(struct tcpm_port *port, const u32 *pdo,
			      unsigned int nr_pdo)
{
	enum pdo_err err_index = tcpm_caps_err(port, pdo, nr_pdo);

	if (err_index != PDO_NO_ERR) {
		tcpm_log_force(port, " %s", pdo_err_msg[err_index]);
		return -EINVAL;
	}

	return 0;
}