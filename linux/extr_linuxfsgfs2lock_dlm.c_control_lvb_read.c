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
struct lm_lockstruct {char* ls_control_lvb; } ;
typedef  char __le32 ;

/* Variables and functions */
 int GDLM_LVB_SIZE ; 
 int /*<<< orphan*/  le32_to_cpu (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void control_lvb_read(struct lm_lockstruct *ls, uint32_t *lvb_gen,
			     char *lvb_bits)
{
	__le32 gen;
	memcpy(lvb_bits, ls->ls_control_lvb, GDLM_LVB_SIZE);
	memcpy(&gen, lvb_bits, sizeof(__le32));
	*lvb_gen = le32_to_cpu(gen);
}