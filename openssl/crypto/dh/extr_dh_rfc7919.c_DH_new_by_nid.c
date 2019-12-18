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
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/  DH_F_DH_NEW_BY_NID ; 
 int /*<<< orphan*/  DH_R_INVALID_PARAMETER_NID ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NID_ffdhe2048 132 
#define  NID_ffdhe3072 131 
#define  NID_ffdhe4096 130 
#define  NID_ffdhe6144 129 
#define  NID_ffdhe8192 128 
 int /*<<< orphan*/  _bignum_ffdhe2048_p ; 
 int /*<<< orphan*/  _bignum_ffdhe3072_p ; 
 int /*<<< orphan*/  _bignum_ffdhe4096_p ; 
 int /*<<< orphan*/  _bignum_ffdhe6144_p ; 
 int /*<<< orphan*/  _bignum_ffdhe8192_p ; 
 int /*<<< orphan*/ * dh_param_init (int /*<<< orphan*/ *,int) ; 

DH *DH_new_by_nid(int nid)
{
    switch (nid) {
    case NID_ffdhe2048:
        return dh_param_init(&_bignum_ffdhe2048_p, 225);
    case NID_ffdhe3072:
        return dh_param_init(&_bignum_ffdhe3072_p, 275);
    case NID_ffdhe4096:
        return dh_param_init(&_bignum_ffdhe4096_p, 325);
    case NID_ffdhe6144:
        return dh_param_init(&_bignum_ffdhe6144_p, 375);
    case NID_ffdhe8192:
        return dh_param_init(&_bignum_ffdhe8192_p, 400);
    default:
        DHerr(DH_F_DH_NEW_BY_NID, DH_R_INVALID_PARAMETER_NID);
        return NULL;
    }
}