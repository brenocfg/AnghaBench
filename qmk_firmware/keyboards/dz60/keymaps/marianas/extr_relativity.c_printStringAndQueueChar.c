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
 scalar_t__* charCount ; 
 size_t charCountLen ; 
 size_t countPointer ; 
 int /*<<< orphan*/  printString (char*) ; 
 int /*<<< orphan*/  printTableAbbreviation () ; 
 int sendAbbr ; 
 char* tableNameList ; 
 int tableNameListLen ; 

void printStringAndQueueChar(char* str)
{
  if (charCount[countPointer] > 0 && countPointer < charCountLen)
  {
    countPointer++;
  }
  sendAbbr = true;
  if (str[0] != '\0')
  {
    printString(str);

    for (int i = 0; i < tableNameListLen-1; i++)
    {
      if (tableNameList[i] == '\0')
      {
        tableNameList[i] = str[0];
        tableNameList[i+1] = '\0';
        break;
      }
      else if (i == tableNameListLen-2)
      {
        printTableAbbreviation();
        break;
      }
    }
    //for (i = 0; i < tableNameListLen && tableNameList[i] > 0; i++)
    //{
    //  send_char(tableNameList[i]);
    //}
    //send_string_P("Darden");
    //send_string_P(&myarray);
    //send_string_P(str);
  }
}