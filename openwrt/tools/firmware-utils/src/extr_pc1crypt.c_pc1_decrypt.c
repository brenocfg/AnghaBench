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
struct pc1_ctx {int cfc; int inter; int cfd; int compte; short* cle; } ;

/* Variables and functions */
 int /*<<< orphan*/  pc1_assemble (struct pc1_ctx*) ; 

__attribute__((used)) static unsigned char pc1_decrypt(struct pc1_ctx *pc1, short c)
{
	pc1_assemble(pc1);
	pc1->cfc = pc1->inter >> 8;
	pc1->cfd = pc1->inter & 255; /* cfc^cfd = random byte */

	c = c ^ (pc1->cfc ^ pc1->cfd);
	for (pc1->compte = 0; pc1->compte <= 15; pc1->compte++) {
		/* we mix the plaintext byte with the key */
		pc1->cle[pc1->compte] = pc1->cle[pc1->compte] ^ c;
	}

	return c;
}