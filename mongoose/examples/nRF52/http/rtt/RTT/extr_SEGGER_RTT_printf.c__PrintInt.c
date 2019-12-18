#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ReturnValue; } ;
typedef  TYPE_1__ SEGGER_RTT_PRINTF_DESC ;

/* Variables and functions */
 unsigned int FORMAT_FLAG_LEFT_JUSTIFY ; 
 unsigned int FORMAT_FLAG_PAD_ZERO ; 
 unsigned int FORMAT_FLAG_PRINT_SIGN ; 
 int /*<<< orphan*/  _PrintUnsigned (TYPE_1__*,int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  _StoreChar (TYPE_1__*,char) ; 

__attribute__((used)) static void _PrintInt(SEGGER_RTT_PRINTF_DESC * pBufferDesc, int v, unsigned Base, unsigned NumDigits, unsigned FieldWidth, unsigned FormatFlags) {
  unsigned Width;
  unsigned Number;

  Number = (v < 0) ? -v : v;

  //
  // Get actual field width
  //
  Width = 1;
  while (Number >= Base) {
    Number = (Number / Base);
    Width++;
  }
  if (NumDigits > Width) {
    Width = NumDigits;
  }
  if ((FieldWidth > 0) && ((v < 0) || ((FormatFlags & FORMAT_FLAG_PRINT_SIGN) == FORMAT_FLAG_PRINT_SIGN))) {
    FieldWidth--;
  }

  //
  // Print leading spaces if necessary
  //
  if ((((FormatFlags & FORMAT_FLAG_PAD_ZERO) == 0) || (NumDigits != 0)) && ((FormatFlags & FORMAT_FLAG_LEFT_JUSTIFY) == 0)) {
    if (FieldWidth != 0) {
      while ((FieldWidth != 0) && (Width < FieldWidth--)) {
        _StoreChar(pBufferDesc, ' ');
        if (pBufferDesc->ReturnValue < 0) {
          return;
        }
      }
    }
  }
  //
  // Print sign if necessary
  //
  if (v < 0) {
    v = -v;
    _StoreChar(pBufferDesc, '-');
    if (pBufferDesc->ReturnValue < 0) {
      return;
    }
  } else if ((FormatFlags & FORMAT_FLAG_PRINT_SIGN) == FORMAT_FLAG_PRINT_SIGN) {
    _StoreChar(pBufferDesc, '+');
    if (pBufferDesc->ReturnValue < 0) {
      return;
    }
  }
  //
  // Print leading zeros if necessary
  //
  if (((FormatFlags & FORMAT_FLAG_PAD_ZERO) == FORMAT_FLAG_PAD_ZERO) && ((FormatFlags & FORMAT_FLAG_LEFT_JUSTIFY) == 0) && (NumDigits == 0)) {
    if (FieldWidth != 0) {
      while ((FieldWidth != 0) && (Width < FieldWidth--)) {
        _StoreChar(pBufferDesc, '0');
        if (pBufferDesc->ReturnValue < 0) {
          return;
        }
      }
    }
  }

  //
  // Print number without sign
  //
  _PrintUnsigned(pBufferDesc, v, Base, NumDigits, FieldWidth, FormatFlags);
}