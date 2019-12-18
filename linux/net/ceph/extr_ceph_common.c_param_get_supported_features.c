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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_FEATURES_SUPPORTED_DEFAULT ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int param_get_supported_features(char *buffer,
					const struct kernel_param *kp)
{
	return sprintf(buffer, "0x%llx", CEPH_FEATURES_SUPPORTED_DEFAULT);
}