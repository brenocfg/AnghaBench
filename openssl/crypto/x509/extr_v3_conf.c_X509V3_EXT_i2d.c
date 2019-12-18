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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/ * X509V3_EXT_get_nid (int) ; 
 int /*<<< orphan*/  X509V3_F_X509V3_EXT_I2D ; 
 int /*<<< orphan*/  X509V3_R_UNKNOWN_EXTENSION ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * do_ext_i2d (int /*<<< orphan*/  const*,int,int,void*) ; 

X509_EXTENSION *X509V3_EXT_i2d(int ext_nid, int crit, void *ext_struc)
{
    const X509V3_EXT_METHOD *method;

    if ((method = X509V3_EXT_get_nid(ext_nid)) == NULL) {
        X509V3err(X509V3_F_X509V3_EXT_I2D, X509V3_R_UNKNOWN_EXTENSION);
        return NULL;
    }
    return do_ext_i2d(method, ext_nid, crit, ext_struc);
}