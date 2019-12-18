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

/* Variables and functions */
 int /*<<< orphan*/  KC_BSPC ; 
 int /*<<< orphan*/ * charCount ; 
 size_t countPointer ; 
 int /*<<< orphan*/  printString (char*) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void ReplaceString(char *orig, char *repl)
{
  int i = 0;
  while((orig[i] != 0x0 && repl[i] != 0x0) && orig[i] == repl[i])
   i++;

  if(orig[i] != 0x0)
  {
    int o = i;
    while (orig[o++] != 0x0) {
      charCount[countPointer]--;
      register_code(KC_BSPC);
      unregister_code(KC_BSPC);
    }
  }
  printString(repl+i);
}