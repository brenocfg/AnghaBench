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
struct TYPE_3__ {int nColorTblLen; scalar_t__* colortbl; int nFontTblLen; } ;
typedef  TYPE_1__ ME_OutStream ;
typedef  scalar_t__ COLORREF ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static BOOL find_color_in_colortbl( ME_OutStream *stream, COLORREF color, unsigned int *idx )
{
    int i;

    *idx = 0;
    for (i = 1; i < stream->nColorTblLen; i++)
    {
        if (stream->colortbl[i] == color)
        {
            *idx = i;
            break;
        }
    }

    return i < stream->nFontTblLen;
}