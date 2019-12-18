#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  H; int /*<<< orphan*/  G; int /*<<< orphan*/  F; int /*<<< orphan*/  E; int /*<<< orphan*/  D; int /*<<< orphan*/  C; int /*<<< orphan*/  B; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ SM3_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SM3_A ; 
 int /*<<< orphan*/  SM3_B ; 
 int /*<<< orphan*/  SM3_C ; 
 int /*<<< orphan*/  SM3_D ; 
 int /*<<< orphan*/  SM3_E ; 
 int /*<<< orphan*/  SM3_F ; 
 int /*<<< orphan*/  SM3_G ; 
 int /*<<< orphan*/  SM3_H ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int sm3_init(SM3_CTX *c)
{
    memset(c, 0, sizeof(*c));
    c->A = SM3_A;
    c->B = SM3_B;
    c->C = SM3_C;
    c->D = SM3_D;
    c->E = SM3_E;
    c->F = SM3_F;
    c->G = SM3_G;
    c->H = SM3_H;
    return 1;
}