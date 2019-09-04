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
struct TYPE_4__ {int /*<<< orphan*/  E; int /*<<< orphan*/  D; int /*<<< orphan*/  C; int /*<<< orphan*/  B; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ RIPEMD160_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  RIPEMD160_A ; 
 int /*<<< orphan*/  RIPEMD160_B ; 
 int /*<<< orphan*/  RIPEMD160_C ; 
 int /*<<< orphan*/  RIPEMD160_D ; 
 int /*<<< orphan*/  RIPEMD160_E ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int RIPEMD160_Init(RIPEMD160_CTX *c)
{
    memset(c, 0, sizeof(*c));
    c->A = RIPEMD160_A;
    c->B = RIPEMD160_B;
    c->C = RIPEMD160_C;
    c->D = RIPEMD160_D;
    c->E = RIPEMD160_E;
    return 1;
}