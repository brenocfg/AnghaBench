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
struct nios2_reg {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NUMREGNAMES ; 
 int /*<<< orphan*/  assert (struct nios2_reg*) ; 
 int nios2_num_regs ; 
 struct nios2_reg* nios2_regs ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct nios2_reg *
nios2_coprocessor_regs (void)
{
  static struct nios2_reg *cached = NULL;
  
  if (!cached)
    {
      int i;
      for (i = NUMREGNAMES; i < nios2_num_regs; i++) {
	      if (!strcmp (nios2_regs[i].name, "c0")) {
		      cached = nios2_regs + i;
		      break;
	      }
      }
      assert (cached);
    }
  return cached;
}