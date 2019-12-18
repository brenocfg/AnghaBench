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
typedef  int /*<<< orphan*/  uint32_t ;
struct lm_lockstruct {int /*<<< orphan*/  ls_control_lvb; } ;
typedef  char __le32 ;

/* Variables and functions */
 int GDLM_LVB_SIZE ; 
 char cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void control_lvb_write(struct lm_lockstruct *ls, uint32_t lvb_gen,
			      char *lvb_bits)
{
	__le32 gen;
	memcpy(ls->ls_control_lvb, lvb_bits, GDLM_LVB_SIZE);
	gen = cpu_to_le32(lvb_gen);
	memcpy(ls->ls_control_lvb, &gen, sizeof(__le32));
}