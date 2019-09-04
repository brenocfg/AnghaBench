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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 long BIO_ctrl (int /*<<< orphan*/ *,int,long,char*) ; 

long BIO_int_ctrl(BIO *b, int cmd, long larg, int iarg)
{
    int i;

    i = iarg;
    return BIO_ctrl(b, cmd, larg, (char *)&i);
}