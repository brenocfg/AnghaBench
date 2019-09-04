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
typedef  enum ud_mnemonic_code { ____Placeholder_ud_mnemonic_code } ud_mnemonic_code ;

/* Variables and functions */
 int UD_MAX_MNEMONIC_CODE ; 
 char const** ud_mnemonics_str ; 

const char*
ud_lookup_mnemonic(enum ud_mnemonic_code c)
{
  if (c < UD_MAX_MNEMONIC_CODE) {
    return ud_mnemonics_str[c];
  } else {
    return NULL;
  }
}