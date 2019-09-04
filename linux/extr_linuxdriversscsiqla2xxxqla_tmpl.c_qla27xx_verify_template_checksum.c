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
struct qla27xx_fwdt_template {int /*<<< orphan*/  template_size; } ;

/* Variables and functions */
 scalar_t__ qla27xx_template_checksum (struct qla27xx_fwdt_template*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
qla27xx_verify_template_checksum(struct qla27xx_fwdt_template *tmp)
{
	return qla27xx_template_checksum(tmp, tmp->template_size) == 0;
}