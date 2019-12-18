#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ciph; } ;
struct TYPE_6__ {scalar_t__ ptr; } ;
struct TYPE_5__ {int block_size; } ;
typedef  TYPE_2__ PX_Cipher ;
typedef  TYPE_3__ OSSLCipher ;

/* Variables and functions */

__attribute__((used)) static unsigned
gen_ossl_block_size(PX_Cipher *c)
{
	OSSLCipher *od = (OSSLCipher *) c->ptr;

	return od->ciph->block_size;
}