#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum textfont_prop_id { ____Placeholder_textfont_prop_id } textfont_prop_id ;
struct TYPE_6__ {int /*<<< orphan*/  str; } ;
struct TYPE_5__ {TYPE_4__* props; int /*<<< orphan*/  range; } ;
typedef  TYPE_1__ ITextFontImpl ;

/* Variables and functions */
 int FONT_NAME ; 
 int FONT_PROPID_FIRST ; 
 int FONT_PROPID_LAST ; 
 int /*<<< orphan*/  get_textfont_prop (TYPE_1__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  textfont_getname_from_range (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void textfont_cache_range_props(ITextFontImpl *font)
{
    enum textfont_prop_id propid;
    for (propid = FONT_PROPID_FIRST; propid < FONT_PROPID_LAST; propid++) {
        if (propid == FONT_NAME)
            textfont_getname_from_range(font->range, &font->props[propid].str);
        else
            get_textfont_prop(font, propid, &font->props[propid]);
    }
}