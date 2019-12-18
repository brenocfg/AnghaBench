#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ dwError; } ;
struct TYPE_7__ {int dwEffects; int /*<<< orphan*/  bUnderlineType; } ;
struct TYPE_8__ {int nColorTblLen; TYPE_1__ cur_fmt; TYPE_3__* stream; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_2__ ME_OutStream ;
typedef  TYPE_3__ EDITSTREAM ;

/* Variables and functions */
 int CFE_AUTOBACKCOLOR ; 
 int CFE_AUTOCOLOR ; 
 int /*<<< orphan*/  CFU_UNDERLINE ; 
 TYPE_2__* heap_alloc_zero (int) ; 

__attribute__((used)) static ME_OutStream*
ME_StreamOutInit(ME_TextEditor *editor, EDITSTREAM *stream)
{
  ME_OutStream *pStream = heap_alloc_zero(sizeof(*pStream));

  pStream->stream = stream;
  pStream->stream->dwError = 0;
  pStream->nColorTblLen = 1;
  pStream->cur_fmt.dwEffects = CFE_AUTOCOLOR | CFE_AUTOBACKCOLOR;
  pStream->cur_fmt.bUnderlineType = CFU_UNDERLINE;
  return pStream;
}