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
struct ud {int mnemonic; } ;
typedef  enum ud_mnemonic_code { ____Placeholder_ud_mnemonic_code } ud_mnemonic_code ;

/* Variables and functions */

enum ud_mnemonic_code
ud_insn_mnemonic(const struct ud *u)
{
  return u->mnemonic;
}