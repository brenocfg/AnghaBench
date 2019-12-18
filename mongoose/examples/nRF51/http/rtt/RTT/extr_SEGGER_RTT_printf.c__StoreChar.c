#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Cnt; int BufferSize; char* pBuffer; int ReturnValue; int /*<<< orphan*/  RTTBufferIndex; } ;
typedef  TYPE_1__ SEGGER_RTT_PRINTF_DESC ;

/* Variables and functions */
 int SEGGER_RTT_Write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void _StoreChar(SEGGER_RTT_PRINTF_DESC * p, char c) {
  int Cnt;

  Cnt = p->Cnt;
  if ((Cnt + 1) <= p->BufferSize) {
    *(p->pBuffer + Cnt) = c;
    p->Cnt = Cnt + 1;
    p->ReturnValue++;
  }
  //
  // Write part of string, when the buffer is full
  //
  if (p->Cnt == p->BufferSize) {
    if (SEGGER_RTT_Write(p->RTTBufferIndex, p->pBuffer, p->Cnt) != p->Cnt) {
      p->ReturnValue = -1;
    } else {
      p->Cnt = 0;
    }
  }
}