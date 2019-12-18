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
struct pc1_ctx {int* x1a0; int* cle; int inter; int res; scalar_t__ i; } ;

/* Variables and functions */
 int /*<<< orphan*/  pc1_code (struct pc1_ctx*) ; 

__attribute__((used)) static void pc1_assemble(struct pc1_ctx *pc1)
{
	pc1->x1a0[0] = (pc1->cle[0] * 256) + pc1->cle[1];

	pc1_code(pc1);
	pc1->inter = pc1->res;

	pc1->x1a0[1] = pc1->x1a0[0] ^ ((pc1->cle[2]*256) + pc1->cle[3]);
	pc1_code(pc1);
	pc1->inter = pc1->inter ^ pc1->res;

	pc1->x1a0[2] = pc1->x1a0[1] ^ ((pc1->cle[4]*256) + pc1->cle[5]);
	pc1_code(pc1);
	pc1->inter = pc1->inter ^ pc1->res;

	pc1->x1a0[3] = pc1->x1a0[2] ^ ((pc1->cle[6]*256) + pc1->cle[7]);
	pc1_code(pc1);
	pc1->inter = pc1->inter ^ pc1->res;

	pc1->x1a0[4] = pc1->x1a0[3] ^ ((pc1->cle[8]*256) + pc1->cle[9]);
	pc1_code(pc1);
	pc1->inter = pc1->inter ^ pc1->res;

	pc1->x1a0[5] = pc1->x1a0[4] ^ ((pc1->cle[10]*256) + pc1->cle[11]);
	pc1_code(pc1);
	pc1->inter = pc1->inter ^ pc1->res;

	pc1->x1a0[6] = pc1->x1a0[5] ^ ((pc1->cle[12]*256) + pc1->cle[13]);
	pc1_code(pc1);
	pc1->inter = pc1->inter ^ pc1->res;

	pc1->x1a0[7] = pc1->x1a0[6] ^ ((pc1->cle[14]*256) + pc1->cle[15]);
	pc1_code(pc1);
	pc1->inter = pc1->inter ^ pc1->res;

	pc1->i = 0;
}