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
typedef  int /*<<< orphan*/  ECPKPARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  ECPKPARAMETERS_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_I2D_ECPKPARAMETERS ; 
 int /*<<< orphan*/ * EC_GROUP_get_ecpkparameters (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_GROUP2PKPARAMETERS_FAILURE ; 
 int /*<<< orphan*/  EC_R_I2D_ECPKPARAMETERS_FAILURE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2d_ECPKPARAMETERS (int /*<<< orphan*/ *,unsigned char**) ; 

int i2d_ECPKParameters(const EC_GROUP *a, unsigned char **out)
{
    int ret = 0;
    ECPKPARAMETERS *tmp = EC_GROUP_get_ecpkparameters(a, NULL);
    if (tmp == NULL) {
        ECerr(EC_F_I2D_ECPKPARAMETERS, EC_R_GROUP2PKPARAMETERS_FAILURE);
        return 0;
    }
    if ((ret = i2d_ECPKPARAMETERS(tmp, out)) == 0) {
        ECerr(EC_F_I2D_ECPKPARAMETERS, EC_R_I2D_ECPKPARAMETERS_FAILURE);
        ECPKPARAMETERS_free(tmp);
        return 0;
    }
    ECPKPARAMETERS_free(tmp);
    return ret;
}