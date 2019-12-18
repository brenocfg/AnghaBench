#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ReturnValue; } ;
typedef  TYPE_1__ SEGGER_RTT_PRINTF_DESC ;

/* Variables and functions */
 unsigned int FORMAT_FLAG_LEFT_JUSTIFY ; 
 unsigned int FORMAT_FLAG_PAD_ZERO ; 
 int /*<<< orphan*/  _StoreChar (TYPE_1__*,char const) ; 

__attribute__((used)) static void _PrintUnsigned(SEGGER_RTT_PRINTF_DESC * pBufferDesc, unsigned v, unsigned Base, int NumDigits, unsigned FieldWidth, unsigned FormatFlags) {
  static const char _aV2C[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
  unsigned Div;
  unsigned Digit = 1;
  unsigned Number;
  unsigned Width;
  char c;

  Number = v;

  //
  // Get actual field width
  //
  Width = 1;
  while (Number >= Base) {
    Number = (Number / Base);
    Width++;
  }
  if ((unsigned)NumDigits > Width) {
    Width = NumDigits;
  }
  //
  // Print leading chars if necessary
  //
  if ((FormatFlags & FORMAT_FLAG_LEFT_JUSTIFY) == 0) {
    if (FieldWidth != 0) {
      if (((FormatFlags & FORMAT_FLAG_PAD_ZERO) == FORMAT_FLAG_PAD_ZERO) && (NumDigits == 0)) {
        c = '0';
      } else {
        c = ' ';
      }
      while ((FieldWidth != 0) && (Width < FieldWidth--)) {
        _StoreChar(pBufferDesc, c);
        if (pBufferDesc->ReturnValue < 0) {
          return;
        }
      }
    }
  }
  //
  // Count how many digits are required by precision
  //
  while (((v / Digit) >= Base) | (NumDigits-- > 1)) {
    Digit *= Base;
  }
  //
  // Output digits
  //
  do {
    Div = v / Digit;
    v -= Div * Digit;
    _StoreChar(pBufferDesc, _aV2C[Div]);
    if (pBufferDesc->ReturnValue < 0) {
      break;
    }
    Digit /= Base;
  } while (Digit);
  //
  // Print trailing spaces if necessary
  //
  if ((FormatFlags & FORMAT_FLAG_LEFT_JUSTIFY) == FORMAT_FLAG_LEFT_JUSTIFY) {
    if (FieldWidth != 0) {
      while ((FieldWidth != 0) && (Width < FieldWidth--)) {
        _StoreChar(pBufferDesc, ' ');
        if (pBufferDesc->ReturnValue < 0) {
          return;
        }
      }
    }
  }
}