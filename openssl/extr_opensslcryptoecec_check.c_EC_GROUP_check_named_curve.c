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
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/ * EC_curve_nid2nist (int) ; 
 int NID_undef ; 
 int ec_curve_nid_from_params (int /*<<< orphan*/  const*) ; 

int EC_GROUP_check_named_curve(const EC_GROUP *group, int nist_only)
{
    int nid;

    nid = ec_curve_nid_from_params(group);
    if (nid > 0 && nist_only && EC_curve_nid2nist(nid) == NULL)
        nid = NID_undef;
    return nid;
}