#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int x; int y; } ;
struct TYPE_23__ {int /*<<< orphan*/  style; TYPE_6__* text; TYPE_5__ pt; } ;
struct TYPE_20__ {int y; } ;
struct TYPE_18__ {scalar_t__ wNumbering; } ;
struct TYPE_24__ {TYPE_7__ para_num; TYPE_4__ pt; TYPE_2__ fmt; } ;
struct TYPE_17__ {TYPE_8__ para; } ;
struct TYPE_25__ {TYPE_1__ member; } ;
struct TYPE_22__ {int /*<<< orphan*/  nLen; int /*<<< orphan*/  szData; } ;
struct TYPE_19__ {int x; int y; } ;
struct TYPE_16__ {int /*<<< orphan*/  hDC; TYPE_3__ pt; } ;
typedef  TYPE_8__ ME_Paragraph ;
typedef  TYPE_9__ ME_DisplayItem ;
typedef  TYPE_10__ ME_Context ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  ExtTextOutW (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_SelectStyleFont (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_UnselectStyleFont (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_text_color (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_para_number( ME_Context *c, ME_DisplayItem *p )
{
    ME_Paragraph *para = &p->member.para;
    HFONT old_font;
    int x, y;
    COLORREF old_text;

    if (para->fmt.wNumbering)
    {
        old_font = ME_SelectStyleFont( c, para->para_num.style );
        old_text = SetTextColor( c->hDC, get_text_color( c, para->para_num.style, FALSE ) );

        x = c->pt.x + para->para_num.pt.x;
        y = c->pt.y + para->pt.y + para->para_num.pt.y;

        ExtTextOutW( c->hDC, x, y, 0, NULL, para->para_num.text->szData, para->para_num.text->nLen, NULL );

        SetTextColor( c->hDC, old_text );
        ME_UnselectStyleFont( c, para->para_num.style, old_font );
    }
}