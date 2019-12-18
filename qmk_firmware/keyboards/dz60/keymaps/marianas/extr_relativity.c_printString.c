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
 int /*<<< orphan*/ * charCount ; 
 size_t countPointer ; 
 int /*<<< orphan*/  send_char (char) ; 

void printString(char* str)
{

  if (str[0] != '\0')
  {
    int i = 0;
    while (true)
    {
      if (str[i] == 0)
      {
        break;
      }
      send_char(str[i++]);
      charCount[countPointer]++;
    }
  }
}