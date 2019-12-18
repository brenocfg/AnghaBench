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
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  int /*<<< orphan*/  DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DES_DECRYPT ; 
 int /*<<< orphan*/  DES_ENCRYPT ; 
 int /*<<< orphan*/  DES_encrypt2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void DES_encrypt3(DES_LONG *data, DES_key_schedule *ks1,
                  DES_key_schedule *ks2, DES_key_schedule *ks3)
{
    register DES_LONG l, r;

    l = data[0];
    r = data[1];
    IP(l, r);
    data[0] = l;
    data[1] = r;
    DES_encrypt2((DES_LONG *)data, ks1, DES_ENCRYPT);
    DES_encrypt2((DES_LONG *)data, ks2, DES_DECRYPT);
    DES_encrypt2((DES_LONG *)data, ks3, DES_ENCRYPT);
    l = data[0];
    r = data[1];
    FP(r, l);
    data[0] = l;
    data[1] = r;
}