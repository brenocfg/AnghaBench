#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ dwSize; scalar_t__ dwUsed; scalar_t__* buffer; TYPE_1__* editstream; } ;
struct TYPE_7__ {TYPE_3__* stream; } ;
struct TYPE_6__ {scalar_t__ dwError; } ;
typedef  TYPE_2__ RTF_Info ;
typedef  TYPE_3__ ME_InStream ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  ME_StreamInFill (TYPE_3__*) ; 

int _RTFGetChar(RTF_Info *info)
{
	int ch;
        ME_InStream *stream = info->stream;

	if (stream->dwSize <= stream->dwUsed)
	{
                ME_StreamInFill(stream);
		/* if error, it's EOF */
		if (stream->editstream->dwError)
			return EOF;
		/* if no bytes read, it's EOF */
		if (stream->dwSize == 0)
			return EOF;
	}
	ch = (unsigned char)stream->buffer[stream->dwUsed++];
	if (!ch)
		 return ' ';
	return ch;
}