#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  dirty_cnt; } ;
struct TYPE_10__ {TYPE_1__* ameth; } ;
struct TYPE_9__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ DH ;

/* Variables and functions */
 int /*<<< orphan*/  DH_F_DH_PARAM_DECODE ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_DH_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_assign (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* d2i_dhp (TYPE_2__*,unsigned char const**,int) ; 

__attribute__((used)) static int dh_param_decode(EVP_PKEY *pkey,
                           const unsigned char **pder, int derlen)
{
    DH *dh;

    if ((dh = d2i_dhp(pkey, pder, derlen)) == NULL) {
        DHerr(DH_F_DH_PARAM_DECODE, ERR_R_DH_LIB);
        return 0;
    }
    dh->dirty_cnt++;
    EVP_PKEY_assign(pkey, pkey->ameth->pkey_id, dh);
    return 1;
}