#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_OP_PUBLIC ; 
 int ecx_key_op (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecx_set_pub_key(EVP_PKEY *pkey, const unsigned char *pub, size_t len)
{
    return ecx_key_op(pkey, pkey->ameth->pkey_id, NULL, pub, len,
                      KEY_OP_PUBLIC);
}