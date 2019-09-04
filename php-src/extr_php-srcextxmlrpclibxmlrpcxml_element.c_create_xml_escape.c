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

__attribute__((used)) static int create_xml_escape(char *pString, unsigned char c)
{
  int counter = 0;

  pString[counter++] = '&';
  pString[counter++] = '#';
  if(c >= 100) {
    pString[counter++] = c / 100 + '0';
    c = c % 100;
  }
  pString[counter++] = c / 10 + '0';
  c = c % 10;

  pString[counter++] = c + '0';
  pString[counter++] = ';';
  return counter;
}