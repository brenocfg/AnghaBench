#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* stream; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwError; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_2__ ME_OutStream ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  EDITSTREAM ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ME_StreamOutFlush (TYPE_2__*) ; 
 int /*<<< orphan*/  ME_StreamOutFree (TYPE_2__*) ; 
 TYPE_2__* ME_StreamOutInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_StreamOutRTF (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  ME_StreamOutText (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/  const*,int,int) ; 
 int SF_RTF ; 
 int SF_TEXT ; 
 int SF_TEXTIZED ; 

LRESULT ME_StreamOutRange(ME_TextEditor *editor, DWORD dwFormat,
                          const ME_Cursor *start,
                          int nChars, EDITSTREAM *stream)
{
  ME_OutStream *pStream = ME_StreamOutInit(editor, stream);

  if (dwFormat & SF_RTF)
    ME_StreamOutRTF(editor, pStream, start, nChars, dwFormat);
  else if (dwFormat & SF_TEXT || dwFormat & SF_TEXTIZED)
    ME_StreamOutText(editor, pStream, start, nChars, dwFormat);
  if (!pStream->stream->dwError)
    ME_StreamOutFlush(pStream);
  return ME_StreamOutFree(pStream);
}