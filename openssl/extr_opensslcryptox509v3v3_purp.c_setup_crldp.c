#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  crldp; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int /*<<< orphan*/  NID_crl_distribution_points ; 
 int /*<<< orphan*/  X509_get_ext_d2i (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_dp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sk_DIST_POINT_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_DIST_POINT_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_crldp(X509 *x)
{
    int i;
    x->crldp = X509_get_ext_d2i(x, NID_crl_distribution_points, NULL, NULL);
    for (i = 0; i < sk_DIST_POINT_num(x->crldp); i++)
        setup_dp(x, sk_DIST_POINT_value(x->crldp, i));
}