#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* buf; } ;
typedef  TYPE_1__ loopargs_t ;

/* Variables and functions */
 scalar_t__ COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_ENCRYPT ; 
 int /*<<< orphan*/  DES_ede3_cbc_encrypt (unsigned char*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_iv ; 
 size_t D_EDE3_DES ; 
 int /*<<< orphan*/ ** c ; 
 int /*<<< orphan*/ * lengths ; 
 int /*<<< orphan*/  sch ; 
 int /*<<< orphan*/  sch2 ; 
 int /*<<< orphan*/  sch3 ; 
 size_t testnum ; 

__attribute__((used)) static int DES_ede3_cbc_encrypt_loop(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    unsigned char *buf = tempargs->buf;
    int count;
    for (count = 0; COND(c[D_EDE3_DES][testnum]); count++)
        DES_ede3_cbc_encrypt(buf, buf, lengths[testnum],
                             &sch, &sch2, &sch3, &DES_iv, DES_ENCRYPT);
    return count;
}