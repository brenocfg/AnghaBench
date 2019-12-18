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
 int /*<<< orphan*/  SEGGER_RTT_Write (int /*<<< orphan*/ ,char*,int) ; 
 int SEGGER_RTT_WriteString (int /*<<< orphan*/ ,char const*) ; 
 int _ActiveTerminal ; 

int SEGGER_RTT_TerminalOut (char TerminalId, const char* s) {
  char ac[2];
  int  r;

  ac[0] = 0xFF;
  if (TerminalId < 10) {
    ac[1] = '0' + TerminalId;
  } else if (TerminalId < 16) {
    ac[1] = 'A' + (TerminalId - 0x0A);
  } else {
    return -1; // RTT only supports up to 16 virtual terminals.
  }
  SEGGER_RTT_Write(0, ac, 2);
  r = SEGGER_RTT_WriteString(0, s);
  if (TerminalId < 10) {
    ac[1] = '0' + _ActiveTerminal;
  } else if (TerminalId < 16) {
    ac[1] = 'A' + (_ActiveTerminal - 0x0A);
  }
  SEGGER_RTT_Write(0, ac, 2);
  return r;
}