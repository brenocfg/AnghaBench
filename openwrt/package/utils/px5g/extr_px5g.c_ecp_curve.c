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
typedef  int /*<<< orphan*/  mbedtls_ecp_group_id ;
struct TYPE_3__ {int /*<<< orphan*/  grp_id; } ;
typedef  TYPE_1__ mbedtls_ecp_curve_info ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ECP_DP_NONE ; 
 int /*<<< orphan*/  MBEDTLS_ECP_DP_SECP256R1 ; 
 int /*<<< orphan*/  MBEDTLS_ECP_DP_SECP384R1 ; 
 int /*<<< orphan*/  MBEDTLS_ECP_DP_SECP521R1 ; 
 TYPE_1__* mbedtls_ecp_curve_info_from_name (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static mbedtls_ecp_group_id ecp_curve(const char *name)
{
	const mbedtls_ecp_curve_info *curve_info;

	if (!strcmp(name, "P-256"))
		return MBEDTLS_ECP_DP_SECP256R1;
	else if (!strcmp(name, "P-384"))
		return MBEDTLS_ECP_DP_SECP384R1;
	else if (!strcmp(name, "P-521"))
		return MBEDTLS_ECP_DP_SECP521R1;
	curve_info = mbedtls_ecp_curve_info_from_name(name);
	if (curve_info == NULL)
		return MBEDTLS_ECP_DP_NONE;
	else
		return curve_info->grp_id;
}