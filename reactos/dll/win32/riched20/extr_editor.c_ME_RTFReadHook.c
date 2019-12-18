#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int rtfClass; size_t stackTop; TYPE_1__* stack; int /*<<< orphan*/  unicodeLength; int /*<<< orphan*/  codePage; int /*<<< orphan*/  style; int /*<<< orphan*/  styleChanged; int /*<<< orphan*/  rtfMajor; } ;
struct TYPE_5__ {int /*<<< orphan*/  unicodeLength; int /*<<< orphan*/  codePage; int /*<<< orphan*/  style; } ;
typedef  TYPE_2__ RTF_Info ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_AddRefStyle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTFFlushOutputBuffer (TYPE_2__*) ; 
 size_t maxStack ; 
#define  rtfBeginGroup 130 
 int rtfEOF ; 
#define  rtfEndGroup 129 
#define  rtfGroup 128 

__attribute__((used)) static void ME_RTFReadHook(RTF_Info *info)
{
  switch(info->rtfClass)
  {
    case rtfGroup:
      switch(info->rtfMajor)
      {
        case rtfBeginGroup:
          if (info->stackTop < maxStack) {
            info->stack[info->stackTop].style = info->style;
            ME_AddRefStyle(info->style);
            info->stack[info->stackTop].codePage = info->codePage;
            info->stack[info->stackTop].unicodeLength = info->unicodeLength;
          }
          info->stackTop++;
          info->styleChanged = FALSE;
          break;
        case rtfEndGroup:
        {
          RTFFlushOutputBuffer(info);
          info->stackTop--;
          if (info->stackTop <= 0)
            info->rtfClass = rtfEOF;
          if (info->stackTop < 0)
            return;

          ME_ReleaseStyle(info->style);
          info->style = info->stack[info->stackTop].style;
          info->codePage = info->stack[info->stackTop].codePage;
          info->unicodeLength = info->stack[info->stackTop].unicodeLength;
          break;
        }
      }
      break;
  }
}