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
 int* charCount ; 
 size_t countPointer ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int* tableNameList ; 
 int tableNameListLen ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void deletePrev(void)
{
  if (countPointer == 0 && charCount[countPointer] == 0)
    return;
  for (int i = 0; i < charCount[countPointer]; i++)
  {
      register_code(KC_BSPC);
      unregister_code(KC_BSPC);
  }
  charCount[countPointer] = 0;
  int i = 1;
  for (;i < tableNameListLen-1; i++)
  {
    if (tableNameList[i] == 0x0)
    {
      break;
    }
  }
  tableNameList[i-1] = 0x0;
  if (countPointer > 0)
  {
    countPointer--;
  }
}